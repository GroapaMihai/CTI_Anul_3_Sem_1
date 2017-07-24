`timescale 1ns / 1ps
`define DEBUG
 
module test_fsm;
 
    // Inputs
    reg clk;
    reg rst;
 
    // Outputs
    wire [7:0] led;
    wire [6:0] address;
    wire [7:0] data;
`ifdef DEBUG
    wire [1:0] debug_state;
`endif
 
    // Instantiate the Unit Under Test (UUT)
    fsm uut (
`ifdef DEBUG
        .debug_state(debug_state),
`endif
        .clk(clk), 
        .rst(rst), 
        .led(led),
        .address(address),
        .data(data)
    );
 
    initial forever
        #5 clk = ~clk;
 
    initial begin
        // Initialize Inputs
        clk = 0;
        rst = 1;
        // Wait 10 ns for global reset to finish
        #10;
        rst = 0;
 
        // Add stimulus here
		  
    end
 
endmodule