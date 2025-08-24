`timescale 1ns / 1ps
module pwm_generator(
    input  logic clk,      
    input  logic reset_n,   
    input  logic [7:0] sample,    
    output logic pwm_out
);
    logic [7:0] pwm;
    always_ff @(posedge clk) begin
        if (reset_n)
            pwm<= 8'd0;
        else
            pwm <= pwm +1;
    end
    assign pwm_out= (pwm< sample);

endmodule