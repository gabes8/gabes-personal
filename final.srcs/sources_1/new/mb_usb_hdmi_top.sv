
`timescale 1ns / 1ps

module pwm_audio_top(
    input logic clk_100MHz,         
    input logic skip_button,  
    input logic volup_button,
    input logic voldown_button,
    input logic rewind_button,
    input logic [3:0] sw,
    
    output logic pwm_out,       
    output logic pwm_outr,
    output logic audioen,  
    output logic hdmi_tmds_clk_p,
    output logic hdmi_tmds_clk_n,
    output logic [2:0] hdmi_tmds_data_p,
    output logic [2:0] hdmi_tmds_data_n 
);
     logic curr_song;
    // ---- clock gen for samplingg ----
    logic clk_44k1;  
    clock_divider clk_gen (
        .clk_in(clk_100MHz),
        .reset_n(sw[3]),
        .clk_out(clk_44k1)
    );

    // ---- ROM ----
    logic [7:0] audio_sample,sample1,sample3;
    logic [17:0] sample_addr;  
    audio_rom rom (
        .clka(clk_100MHz),
        .addra(sample_addr),
        .douta(sample1),
        .ena(curr_song==1'd0)
    );
    audio_rom2 rom2(
        .clka(clk_100MHz),
        .addra(sample_addr),
        .douta(sample3),
        .ena(curr_song==1'd1)
    );
    // ---- buttons ----
    button_debouncer debouncer (
        .clk(clk_100MHz),
        .button_in(skip_button),
        .pulse_out(skipp)
    );
    button_debouncer volumeup_deb (
        .clk(clk_100MHz),
        .button_in(volup_button),
        .pulse_out(volup)
    );
    button_debouncer volumedown_deb (
        .clk(clk_100MHz),
        .button_in(voldown_button),
        .pulse_out(voldown)
    );    
    button_debouncer rewind_deb (
        .clk(clk_100MHz),
        .button_in(rewind_button),
        .pulse_out(rewindp)
    );
    // ---- song logic ----
    logic [17:0] song_length;
    always_comb begin
        case (curr_song)
            1'd0: begin
                song_length =18'd160000;
                audio_sample = sample1;
            end
            1'd1: begin
                song_length =18'd136000;
                audio_sample =sample3;
            end
            default: begin
                song_length = 18'd0;
                audio_sample= 8'd0;
            end
        endcase
    end
    // ---- music logic ----
    logic p;
    logic halfs;
    logic [2:0] volume = 3'd2;
    logic [7:0] audio_final;
    assign p = sw[2];
    always_ff @(posedge clk_100MHz) begin
        if (sw[3]) begin
            curr_song <=1'd0;
            sample_addr <=18'd0;       
        end else begin
            if (skipp) begin
                curr_song <= (curr_song + 1)%2;
                sample_addr<= 18'd0;
            end
            else if(volup && volume<3'd4) begin
                volume<= volume + 3'd1;
            end
            else if(voldown && volume>3'd0) begin
                volume <= volume-3'd1;            
            end
            else if(rewindp) begin
                sample_addr <=18'd0;
            end
            else if (clk_44k1 && !p) begin
                halfs<= ~halfs;
                case (sw[1:0])
                    2'b01: begin 
                        if (sample_addr< song_length-2)
                            sample_addr<= sample_addr +2;
                        else begin
                            sample_addr<=0;
                            curr_song<= (curr_song + 1)%2;
                        end
                    end
                    2'b10: begin 
                        if (halfs) begin
                            if (sample_addr < song_length-1)
                                sample_addr<=sample_addr +1;
                            else begin
                                sample_addr <= 0;
                                curr_song<=(curr_song +1)%2;
                            end
                        end
                    end
                    default: begin 
                        if (sample_addr <song_length -1)
                            sample_addr<= sample_addr+1;
                        else begin
                            sample_addr <=0;
                            curr_song<= (curr_song + 1) % 2;
                        end
                    end
                endcase
            end
        end
    end
always_comb begin
    case (volume)
        3'd0: audio_final = 8'd0;                          
        3'd1: audio_final = (audio_sample >> 2);
        3'd2: audio_final = (audio_sample >> 1);
        3'd3: audio_final = ((audio_sample * 3) >> 2);
        3'd4: audio_final = audio_sample; 
        default: audio_final = audio_sample ;
    endcase
end
    // ---- PWM ----
    pwm_generator pwm (
        .clk(clk_100MHz),
        .reset_n(sw[3]),
        .sample(audio_final),
        .pwm_out(pwm_out)
    );
    assign pwm_outr=pwm_out;
    assign audioen =1'b1;
    //----New Clock----
    logic clk_25MHz, clk_125MHz, clk_locked;
    clk_wiz_0 clk_wiz_inst (
        .clk_out1(clk_25MHz),
        .clk_out2(clk_125MHz),
        .reset(sw[3]),
        .locked(clk_locked),
        .clk_in1(clk_100MHz)
    );
    //---- VGA Controller----
    logic [9:0] drawX, drawY;
    logic hsync, vsync, vde;
    vga_controller vga_inst (
        .pixel_clk(clk_25MHz),
        .reset(sw[3]),
        .hs(hsync),
        .vs(vsync),
        .active_nblank(vde),
        .drawX(drawX),
        .drawY(drawY)
    );   
    //---- Ball ----
    logic[7:0] rot;
    logic[9:0] BallX, BallY, BallS;
    ball ball0( 
        .Reset(sw[3]), 
        .frame_clk(vsync),
        .pause_button(p),
        .BallX(BallX), 
        .BallY(BallY), 
        .BallS(BallS),
        .rotation_counter(rot)
);
    //---- Color Mapper ----
    logic[3:0] recR,recG,recB;
//    logic [3:0] red, green, blue;
    color_mapper color_1 (
        .BallX(BallX),
        .BallY(BallY),
        .Ball_size(BallS),
        .DrawX(drawX),
        .DrawY(drawY),
        .rotation_idx(rot[4:2]),
        .paused(p),
        .curr_song(curr_song),
        .volume(volume),
        .Red(recR),
        .Green(recG),
        .Blue(recB)
    );
//    //---- Song Bar ----
logic        bar;
logic [3:0]  barR, barG, barB;

song_bar song_bar_1 (
    .clk         (clk_100MHz), 
    .reset_n     (sw[3]),
    .DrawX       (drawX),
    .DrawY       (drawY),
    .sample_addr (sample_addr),
    .song_length (song_length),
    .bar_on      (bar),
    .Red         (barR),
    .Green       (barG),
    .Blue        (barB)
);

    //---- Draw Logic ----
logic [3:0] nred, ngreen, nblue;
logic [3:0] red, green, blue;
always_comb begin
    if (bar) begin
        nred = barR;
        ngreen = barG;
        nblue = barB;
    end else begin
        nred = recR;
        ngreen = recG;
        nblue = recB;
    end
end
always_ff@(posedge clk_100MHz)begin
    if(sw[3]) begin
        red<=0;
        green<=0;
        blue<=0;
    end else begin
        red<=nred;
        green<=ngreen;
        blue<=nblue;
    end
end
    //---- HDMI Output----
    hdmi_tx_0 hdmi_inst (
        .pix_clk(clk_25MHz),
        .pix_clkx5(clk_125MHz),
        .pix_clk_locked(clk_locked),
        .rst(sw[3]),
        .red(red),
        .green(green),
        .blue(blue),
        .hsync(hsync),
        .vsync(vsync),
        .vde(vde),
        .aux0_din(4'd0),
        .aux1_din(4'd0),
        .aux2_din(4'd0),
        .ade(1'b0),
        .TMDS_CLK_P(hdmi_tmds_clk_p),
        .TMDS_CLK_N(hdmi_tmds_clk_n),
        .TMDS_DATA_P(hdmi_tmds_data_p),
        .TMDS_DATA_N(hdmi_tmds_data_n)
    );
endmodule