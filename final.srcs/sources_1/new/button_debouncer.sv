`timescale 1ns / 1ps

module button_debouncer (
    input logic clk,         
    input logic button_in,   
    output logic pulse_out    
);
    logic [1:0] sync;
    logic [19:0] count;
    logic st, last;
    always_ff @(posedge clk) begin
        sync[0]<= button_in;
        sync[1] <= sync[0];
        if (sync[1] == st) begin
            count <=0;
        end else begin
            count <=count +1;
            if (&count)
                st <= sync[1];
        end
        last <= st;
        pulse_out <= (st == 1'b1&& last== 1'b0);  
    end
endmodule
