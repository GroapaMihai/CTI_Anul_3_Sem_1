`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:32:17 10/17/2015
// Design Name:   sram2
// Module Name:   C:/Users/student/Desktop/lab2 CN2/lab2/test_sram2.v
// Project Name:  lab2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: sram2
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test_sram2;

	// Inputs
	reg clk;
	reg oe;
	reg cs;
	reg we;
	reg [6:0] address;
	//reg [7:0] data_in;

	// Outputs
	//wire [7:0] data_out;
	wire [7:0] data;
	reg [7:0] buffer;
	
	// Instantiate the Unit Under Test (UUT)
	sram2 uut (
		.clk(clk), 
		.oe(oe), 
		.cs(cs), 
		.we(we), 
		.address(address), 
		.data(data)
	);

	assign data = (oe && !we) ? 8'bz : buffer;
	initial begin
		// Initialize Inputs
		clk = 0;
		oe = 0;
		cs = 0;
		we = 0;
		address = 0;
		buffer = 0;
		
		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		we = 1;
      address = 0;
      buffer = 73; // mem[0] = 73;
      #15;
      address = 1;
      buffer = 19; // mem[1] = 19;
      #10;
      address = 2;
      buffer = 34; // mem[2] = 34;
      #10;
      address = 0;
      we = 0;
      #10;
      address = 1;
      #10;
      cs = 0;
      address = 2;
      #10;
      oe = 0;
		
	end
	
	
      
endmodule

