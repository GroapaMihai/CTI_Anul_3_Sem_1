`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:31:10 10/17/2015 
// Design Name: 
// Module Name:    sram2 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sram2 (
        input  wire       clk,     // clock
        input  wire       oe,      // output enable, active high
        input  wire       cs,      // chip select, active high
        input  wire       we,      // write enable: 0 = read, 1 = write
        input  wire [6:0] address, // adrese pentru 128 de intrari
        inout  wire [7:0] data     // magistrala de date de 8 biti bidirectionala
    );
 
    reg [7:0] memory[0:6];
    reg [7:0] buffer;
 
    always @(negedge clk)
    begin
        if (cs) begin
            if (we) begin
                memory[address] <= data;
            end else begin
                buffer <= memory[address];
            end
        end
    end
 
    assign data = (oe && !we) ? buffer : 8'bz;
 
endmodule
