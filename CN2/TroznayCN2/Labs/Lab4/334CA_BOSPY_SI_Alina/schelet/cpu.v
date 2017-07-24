`include "defines.vh"
module cpu #(
        parameter INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter DATA_WIDTH   = 8,    // registers are 8 bits in width
        parameter I_ADDR_WIDTH = 10,   // 2 * 1024 bytes of flash (or ROM in our case)
        parameter D_ADDR_WIDTH = 7,    // 128 bytes of SRAM
        parameter R_ADDR_WIDTH = 5     // 32 registers
    )(
`ifdef DEBUG
        output wire [2:0]              debug_state,
        output wire [I_ADDR_WIDTH-1:0] debug_program_counter,
        output wire [INSTR_WIDTH-1:0]  debug_instruction,
        output wire [7:0]              debug_sreg,
        output wire [R_ADDR_WIDTH-1:0] debug_rr_addr,
        output wire [R_ADDR_WIDTH-1:0] debug_rd_addr,
        output wire [DATA_WIDTH-1:0]   debug_rr_data,
        output wire [DATA_WIDTH-1:0]   debug_rd_data,
        output wire                    debug_rr_cs,
        output wire                    debug_rd_cs,
        output wire                    debug_rr_we,
        output wire                    debug_rd_we,
        output wire                    debug_rr_oe,
        output wire                    debug_rd_oe,
        output wire [DATA_WIDTH-1:0]   debug_alu_rr,
        output wire [DATA_WIDTH-1:0]   debug_alu_rd,
        output wire                    debug_alu_enable,
        output wire [7:0]              debug_alu_opsel,
        output wire [DATA_WIDTH-1:0]   debug_alu_out,
        output wire [7:0]              debug_alu_flags_out,
        output wire [7:0]              debug_opcode_type,
        output wire [DATA_WIDTH-1:0]   debug_writeback_value,
        output wire [INSTR_WIDTH-1:0]  debug_instr_buffer,
        output wire [D_ADDR_WIDTH-1:0] debug_mem_addr,
        inout  wire [DATA_WIDTH-1:0]   debug_mem_data,
        output wire                    debug_mem_cs,
        output wire                    debug_mem_we,
        output wire                    debug_mem_oe,
`endif
        input wire clk,
        input wire reset
    );

    wire [2:0]              state;
    wire [I_ADDR_WIDTH-1:0] program_counter;
    wire [INSTR_WIDTH-1:0]  instruction;
    wire [R_ADDR_WIDTH-1:0] rr_addr;
    wire [R_ADDR_WIDTH-1:0] rd_addr;
    wire [DATA_WIDTH-1:0]   rr_data;
    wire [DATA_WIDTH-1:0]   rd_data;
    wire                    rr_cs;
    wire                    rd_cs;
    wire                    rr_we;
    wire                    rd_we;
    wire                    rr_oe;
    wire                    rd_oe;
    wire                    alu_enable;
    wire [7:0]              alu_opsel;
    wire [DATA_WIDTH-1:0]   alu_rr;
    wire [DATA_WIDTH-1:0]   alu_rd;
    wire [DATA_WIDTH-1:0]   alu_out;
    wire [7:0]              alu_flags_in;
    wire [7:0]              alu_flags_out;
    wire [D_ADDR_WIDTH-1:0] mem_addr;
    wire [DATA_WIDTH-1:0]   mem_data;
    wire                    mem_cs;
    wire                    mem_we;
    wire                    mem_oe;

`ifdef DEBUG
    assign debug_state = state;
    assign debug_program_counter = program_counter;
    assign debug_instruction = instruction;
    assign debug_rr_addr = rr_addr;
    assign debug_rd_addr = rd_addr;
    assign debug_rr_data = rr_data;
    assign debug_rd_data = rd_data;
    assign debug_rr_cs = rr_cs;
    assign debug_rd_cs = rd_cs;
    assign debug_rr_oe = rr_oe;
    assign debug_rd_oe = rd_oe;
    assign debug_rr_we = rr_we;
    assign debug_rd_we = rd_we;
    assign debug_alu_rr = alu_rr;
    assign debug_alu_rd = alu_rd;
    assign debug_alu_enable = alu_enable;
    assign debug_alu_opsel = alu_opsel;
    assign debug_alu_out = alu_out;
    assign debug_alu_flags_out = alu_flags_out;
    assign debug_mem_addr = mem_addr;
    assign debug_mem_data = mem_data;
    assign debug_mem_cs = mem_cs;
    assign debug_mem_we = mem_we;
    assign debug_mem_oe = mem_oe;
`endif

    control_unit #(
        .DATA_WIDTH(DATA_WIDTH),
        .INSTR_WIDTH(INSTR_WIDTH),
        .D_ADDR_WIDTH(D_ADDR_WIDTH),
        .I_ADDR_WIDTH(I_ADDR_WIDTH),
        .R_ADDR_WIDTH(R_ADDR_WIDTH)
    ) control (
`ifdef DEBUG
        .debug_opcode_type(debug_opcode_type),
        .debug_instr_buffer(debug_instr_buffer),
        .debug_writeback_value(debug_writeback_value),
        .debug_sreg(debug_sreg),
`endif
        .program_counter(program_counter),
        .instruction(instruction),
        .state(state),
        .clk(clk),
        .reset(reset),
        .rr_addr(rr_addr),
        .rd_addr(rd_addr),
        .rr_data(rr_data),
        .rd_data(rd_data),
        .rr_cs(rr_cs),
        .rd_cs(rd_cs),
        .rr_we(rr_we),
        .rd_we(rd_we),
        .rr_oe(rr_oe),
        .rd_oe(rd_oe),
        .alu_enable(alu_enable),
        .alu_opsel(alu_opsel),
        .alu_flags_in(alu_flags_in),
        .alu_flags_out(alu_flags_out),
        .alu_rr(alu_rr),
        .alu_rd(alu_rd),
        .alu_out(alu_out),
        .mem_addr(mem_addr),
        .mem_data(mem_data),
        .mem_cs(mem_cs),
        .mem_we(mem_we),
        .mem_oe(mem_oe)
    );

    alu #(
        .DATA_WIDTH(DATA_WIDTH)
    ) ual (
        .opsel(alu_opsel),
        .enable(alu_enable),
        .rd(alu_rd),
        .rr(alu_rr),
        .out(alu_out),
        .flags_in(alu_flags_in),
        .flags_out(alu_flags_out)
    );

    dual_port_sram #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(R_ADDR_WIDTH)
    ) reg_file (
        .clk(clk),
        .rr_addr(rr_addr),
        .rd_addr(rd_addr),
        .rr_data(rr_data),
        .rd_data(rd_data),
        .rr_cs(rr_cs),
        .rd_cs(rd_cs),
        .rr_we(rr_we),
        .rd_we(rd_we),
        .rr_oe(rr_oe),
        .rd_oe(rd_oe)
    );

    rom #(
        .DATA_WIDTH(INSTR_WIDTH),
        .ADDR_WIDTH(I_ADDR_WIDTH)
    ) instruction_mem (
        .addr(program_counter),
        .data(instruction)
    );

    sram #(
        .ADDR_WIDTH(D_ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH)
    ) data_mem (
        .clk(clk),
        .oe(mem_oe),
        .cs(mem_cs),
        .we(mem_we),
        .address(mem_addr),
        .data(mem_data)
    );

endmodule
