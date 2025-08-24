`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/20/2025 04:15:51 PM
// Design Name: 
// Module Name: audio_rom
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module audio_rom(
    input  logic clk,
    input  logic [17:0] addr,
    output logic [7:0] dout
);

    (* rom_style = "block" *) logic [7:0] rom [0:262143];

    initial begin
        $readmemh("audio.hex", rom);  // Load preprocessed audio
    end

    always_ff @(posedge clk) begin
        dout <= rom[addr];
    end
endmodule
