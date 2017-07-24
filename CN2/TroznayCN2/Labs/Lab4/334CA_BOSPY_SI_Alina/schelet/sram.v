`include "defines.vh"
module sram #(
        parameter DATA_WIDTH  = 8,
        parameter ADDR_WIDTH  = 7       // 128 bytes of SRAM
    )(
        input  wire                  clk,
        input  wire                  oe,
        input  wire                  cs,
        input  wire                  we,
        input  wire [ADDR_WIDTH-1:0] address,
        inout  wire [DATA_WIDTH-1:0] data
    );
 
    reg [DATA_WIDTH-1:0] memory[0:(1<<ADDR_WIDTH)-1];
    reg [DATA_WIDTH-1:0] buffer;
 
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
 
	
    assign data = 8'b01010101;//(cs && oe && !we) ? buffer : {DATA_WIDTH{1'bz}};
 
endmodule
