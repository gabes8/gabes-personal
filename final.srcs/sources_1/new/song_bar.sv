`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/04/2025 01:15:09 PM
// Design Name: 
// Module Name: song_bar
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


module song_bar(
    input  logic clk, 
    input  logic reset_n,      
    input  logic [9:0] DrawX,        
    input  logic [9:0] DrawY,         
    input  logic [17:0] sample_addr,  
    input  logic [17:0] song_length,   
    output logic bar_on,       
    output logic [3:0] Red, Green, Blue
    );
    logic [17:0] ad;
    logic [26:0] long;
    logic [17:0] lg;
    always_ff @(posedge clk) begin
        if (reset_n)begin
            ad <=0;        
            long<= 0;
            lg <=0;
        end else begin
            ad <=sample_addr;                 
            long<= ad*640;
            lg <=song_length;
        end
    end
    logic [9:0] fillb;
    always_ff @(posedge clk) begin
        if (reset_n)           
            fillb <=0;
        else if (lg !=0)    
            fillb <=long / lg;
        else                    
            fillb <=0;
    end
    logic area;
    always_comb begin
        area =(DrawY >=360)&&(DrawY < 370);
        bar_on= area&&(DrawX < fillb);
        if(bar_on)       
            {Red,Green,Blue} = {4'hF,4'hF,4'hF};  
        else if(area)    
            {Red,Green,Blue} = {4'h2,4'h2,4'h2};  
        else                   
            {Red,Green,Blue} = {4'h0,4'h0,4'h0};  
    end

endmodule
