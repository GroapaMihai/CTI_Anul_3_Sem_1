`include "defines.vh"
`timescale 1ns / 1ps
module cpu_test;
    // Inputs
    reg clk;
    reg reset;
    
    localparam INSTR_WIDTH  = 16,      // instructions are 16 bits in width
               DATA_WIDTH   = 8,       // registers are 8 bits in width
               I_ADDR_WIDTH = 10,      // 2 * 1024 bytes of flash (or ROM in our case)
               D_ADDR_WIDTH = 7,       // 128 bytes of SRAM
               R_ADDR_WIDTH = 5;       // 32 registers
    // Outputs
`ifdef DEBUG
    wire [2:0]              state;
    wire [I_ADDR_WIDTH-1:0] program_counter;
    wire [INSTR_WIDTH-1:0]  instruction;
    wire [INSTR_WIDTH-1:0]  instr_buffer;
    wire [7:0]              sreg;
    wire [7:0]              opcode_type;
    wire [DATA_WIDTH-1:0]   writeback_value;
    wire                    rr_cs;
    wire                    rd_cs;
    wire                    rr_we;
    wire                    rd_we;
    wire                    rr_oe;
    wire                    rd_oe;
    wire [R_ADDR_WIDTH-1:0] rr_addr;
    wire [R_ADDR_WIDTH-1:0] rd_addr;
    wire [DATA_WIDTH-1:0]   rr_data;
    wire [DATA_WIDTH-1:0]   rd_data;
    wire [DATA_WIDTH-1:0]   alu_rd;
    wire [DATA_WIDTH-1:0]   alu_rr;
    wire                    alu_enable;
    wire [7:0]              alu_opsel;
    wire [DATA_WIDTH-1:0]   alu_out;
    wire [7:0]              alu_flags_in;
    wire [7:0]              alu_flags_out;
    wire [D_ADDR_WIDTH-1:0] mem_addr;
    wire [DATA_WIDTH-1:0]   mem_data;
    wire                    mem_cs;
    wire                    mem_we;
    wire                    mem_oe;
`endif

    // Instantiate the Unit Under Test (UUT)
    cpu #(
        .DATA_WIDTH(8),         // registers are 8 bits in width
        .INSTR_WIDTH(16),       // instructions are 16 bits in width
        .I_ADDR_WIDTH(10),      // 2 * 1024 bytes of flash (or ROM in our case)
        .D_ADDR_WIDTH(7),       // 128 bytes of SRAM
        .R_ADDR_WIDTH(5)        // 32 registers
    ) uut (
`ifdef DEBUG
        .debug_state(state), 
        .debug_program_counter(program_counter), 
        .debug_sreg(sreg),
        .debug_instruction(instruction), 
        .debug_writeback_value(writeback_value),
        .debug_rr_addr(rr_addr), 
        .debug_rd_addr(rd_addr), 
        .debug_rr_data(rr_data), 
        .debug_rd_data(rd_data), 
        .debug_rr_cs(rr_cs), 
        .debug_rd_cs(rd_cs), 
        .debug_rr_we(rr_we), 
        .debug_rd_we(rd_we), 
        .debug_rr_oe(rr_oe),
        .debug_rd_oe(rd_oe),
        .debug_alu_rd(alu_rd),
        .debug_alu_rr(alu_rr),
        .debug_alu_enable(alu_enable), 
        .debug_alu_opsel(alu_opsel), 
        .debug_alu_out(alu_out),
        .debug_alu_flags_out(alu_flags_out), 
        .debug_opcode_type(opcode_type), 
        .debug_instr_buffer(instr_buffer),
        .debug_mem_addr(mem_addr),
        .debug_mem_data(mem_data),
        .debug_mem_cs(mem_cs),
        .debug_mem_oe(mem_oe),
        .debug_mem_we(mem_we),
`endif
        .clk(clk), 
        .reset(reset)
    );

    initial begin
        // Initialize Inputs
        clk = 1;
        reset = 1;
        // Wait 10 ns for global reset to finish
        #10;
        reset = 0;
    end
    always clk = #5 ~clk;

endmodule
