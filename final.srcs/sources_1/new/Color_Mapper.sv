//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    Stephen Kempf                                                      --
//    3-1-06                                                             --
//                                                                       --
//    Modified by David Kesler  07-16-2008                               --
//    Translated by Joe Meng    07-07-2013                               --
//    Modified by Zuofu Cheng   08-19-2023                               --
//                                                                       --
//    Fall 2023 Distribution                                             --
//                                                                       --
//    For use with ECE 385 USB + HDMI                                    --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------


module  color_mapper ( 
    input logic [9:0] BallX, BallY, DrawX, DrawY, Ball_size,
    input logic [2:0] rotation_idx,
    input logic paused,
    output logic [3:0] Red, Green, Blue 
);
//Spinning record
    // Spinning record
    logic signed [10:0] dx = DrawX - BallX;
    logic signed [10:0] dy = DrawY - BallY;
    logic [23:0] dist2 = dx*dx + dy*dy;

    logic [23:0] R_sq = Ball_size*Ball_size;
    logic [23:0] R_inner_sq = (Ball_size - 4)*(Ball_size - 4);
    logic [23:0] hole_radius_sq = 36;
    logic in_ring = (dist2 <= R_sq) && (dist2 >= R_inner_sq);
    logic in_hole = (dist2 <= hole_radius_sq);

    logic [2:0] sector;
    always_comb begin
        if (dx >= 0 && dy >= 0)         
            sector = (dx > dy) ? 3'd0 : 3'd1;
        else if (dx < 0 && dy >= 0)    
            sector = (-dx > dy) ? 3'd2 : 3'd3;
        else if (dx < 0 && dy < 0)    
            sector = (-dx > -dy) ? 3'd4 : 3'd5;
        else                             
            sector = (dx > -dy) ? 3'd6 : 3'd7;
    end

    logic [2:0] idx = rotation_idx;
    logic [2:0] opp_idx = idx + 3'd4;
    //pause/play
    parameter int BUTTON_X = 270;
    parameter int BUTTON_Y = 300;
    parameter int BUTTON_W = 100;
    parameter int BUTTON_H = 30;
    logic in_button_box = (DrawX >= BUTTON_X)&&(DrawX < BUTTON_X + BUTTON_W)&&(DrawY >= BUTTON_Y)&&(DrawY < BUTTON_Y + BUTTON_H);
    logic in_pause_icon = in_button_box&&paused&&(DrawX >= BUTTON_X + 40&&DrawX < BUTTON_X + 45||DrawX >= BUTTON_X + 55&&DrawX < BUTTON_X + 60)&&(DrawY >= BUTTON_Y + 5&&DrawY < BUTTON_Y + BUTTON_H - 5);
    logic in_play_icon = in_button_box && !paused &&
        (DrawX >= BUTTON_X + 41) && (DrawX < BUTTON_X + 60) &&
        ((DrawY - (BUTTON_Y+5))*3 >= (DrawX - (BUTTON_X + 41))*3) &&
        ((DrawY - (BUTTON_Y+5))*3 <= ((BUTTON_X + 60) - DrawX)*3) &&
        (DrawY >= BUTTON_Y + 5) && (DrawY < BUTTON_Y + BUTTON_H - 5);
    always_comb begin
        Red = 4'd0;
        Green = 4'd0;
        Blue = 4'd0;
        if (dist2 <= R_sq) begin
            if (in_hole) begin
                Red = 4'd0;
                Green = 4'd0;
                Blue = 4'd0;
            end
            else if (in_ring && (sector == idx || sector == opp_idx[2:0])) begin
                Red = 4'hF;
                Green = 4'hF;
                Blue = 4'hF;
            end
            else begin
                Red = 4'h0;
                Green = 4'h4;
                Blue = 4'h1;
            end
        end
        if (in_play_icon || in_pause_icon) begin
            Red = 4'hF;
            Green = 4'hF;
            Blue = 4'hF;
        end else if (in_button_box) begin
            Red = 4'h2;
            Green = 4'h2;
            Blue = 4'h2;
        end
    end
endmodule
