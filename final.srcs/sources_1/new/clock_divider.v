`timescale 1ns / 1ps
module clock_divider(
    input logic clk_in,
    input logic reset_n,
    output logic clk_out
);
    logic [$clog2(12500)-1:0] coun;
    always_ff @(posedge clk_in) begin
        if (reset_n) begin
            coun<= {$clog2(12500){1'b0}};
            clk_out <=1'd0;
        end else if (coun == 12500-1) begin
            coun<= {$clog2(12500){1'b0}};
            clk_out <=1'd1;
        end else begin
            coun<= coun +1;
            clk_out <=1'd0;
        end
    end
endmodule
