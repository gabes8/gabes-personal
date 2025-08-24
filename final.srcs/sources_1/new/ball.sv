//-------------------------------------------------------------------------
//    Ball.sv                                                            --
//    Viral Mehta                                                        --
//    Spring 2005                                                        --
//                                                                       --
//    Modified by Stephen Kempf     03-01-2006                           --
//                                  03-12-2007                           --
//    Translated by Joe Meng        07-07-2013                           --
//    Modified by Zuofu Cheng       08-19-2023                           --
//    Modified by Satvik Yellanki   12-17-2023                           --
//    Fall 2024 Distribution                                             --
//                                                                       --
//    For use with ECE 385 USB + HDMI Lab                                --
//    UIUC ECE Department                                                --
//-------------------------------------------------------------------------


module  ball 
( 
    input logic Reset, 
    input logic frame_clk,
    input logic pause_button,
    output logic [9:0] BallX, 
    output logic [9:0] BallY, 
    output logic [9:0] BallS,
    output logic [7:0] rotation_counter
);
    parameter [9:0] Ball_X_Center=320;  // Center position on the X axis
    parameter [9:0] Ball_Y_Center=240;  // Center position on the Y axis
    parameter [9:0] Ball_Radius = 40;
    assign BallX = Ball_X_Center;
    assign BallY = Ball_Y_Center;
    assign BallS = Ball_Radius;
    logic [1:0] frame_divider;
    always_ff@(posedge frame_clk) begin
        if(Reset) begin
            rotation_counter <= 8'd0;
            frame_divider <= 2'd0;
        end else if(!pause_button) begin
            frame_divider <= frame_divider + 1'b1;
            rotation_counter <= rotation_counter;
            if(frame_divider == 2'd3) begin
                frame_divider <= 2'd0;
                rotation_counter <= rotation_counter  + 1'b1;
            end 
        end else begin
            rotation_counter <= rotation_counter;
            frame_divider <= 2'd0;
        end
    end

endmodule
