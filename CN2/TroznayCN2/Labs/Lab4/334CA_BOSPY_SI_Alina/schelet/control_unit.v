`include "defines.vh"
module control_unit #(
        parameter INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter DATA_WIDTH   = 8,    // registers are 8 bits in width
        parameter I_ADDR_WIDTH = 10,   // 2 * 1024 bytes of flash (or ROM in our case)
        parameter D_ADDR_WIDTH = 7,    // 128 bytes of SRAM
        parameter R_ADDR_WIDTH = 5     // 32 registers
    )(
`ifdef DEBUG
        output wire [7:0]              debug_opcode_type,
        output wire [7:0]              debug_opcode_group,
        output wire [INSTR_WIDTH-1:0]  debug_instr_buffer,
        output wire [DATA_WIDTH-1:0]   debug_writeback_value,
        output wire [7:0]              debug_sreg,
`endif
        output reg  [I_ADDR_WIDTH-1:0] program_counter,
        input  wire [INSTR_WIDTH-1:0]  instruction,
        output wire [2:0]              state,
        input  wire                    clk,
        input  wire                    reset,
        output wire [R_ADDR_WIDTH-1:0] rr_addr,
        output wire [R_ADDR_WIDTH-1:0] rd_addr,
        inout  wire [DATA_WIDTH-1:0]   rr_data,
        inout  wire [DATA_WIDTH-1:0]   rd_data,
        output wire                    rr_cs,
        output wire                    rd_cs,
        output wire                    rr_we,
        output wire                    rd_we,
        output wire                    rr_oe,
        output wire                    rd_oe,
        output wire                    alu_enable,
        output reg  [7:0]              alu_opsel,
        output wire [7:0]              alu_flags_in,
        input  wire [7:0]              alu_flags_out,
        output reg  [DATA_WIDTH-1:0]   alu_rr,
        output reg  [DATA_WIDTH-1:0]   alu_rd,
        input  wire [DATA_WIDTH-1:0]   alu_out,
        output wire [D_ADDR_WIDTH-1:0] mem_addr,
        inout  wire [DATA_WIDTH-1:0]   mem_data,
        output wire                    mem_cs,
        output wire                    mem_we,
        output wire                    mem_oe
    );

    reg  [INSTR_WIDTH-1:0]  instr_buffer;
    reg  [DATA_WIDTH-1:0]   alu_out_buffer;
    reg  [7:0]              sreg;
    wire [7:0]              opcode_type;
    wire [7:0]              opcode_group;
    wire [DATA_WIDTH-1:0]   writeback_value;
    wire [D_ADDR_WIDTH-1:0] indirect_addr;
    wire [DATA_WIDTH-1:0]   data_to_write_to_mem;
    wire                    opc_arithmetic;

`ifdef DEBUG
    assign debug_opcode_type     = opcode_type;
    assign debug_instr_buffer    = instr_buffer;
    assign debug_writeback_value = writeback_value;
    assign debug_sreg            = sreg;
`endif

    state_machine fsm (
        .state(state),
        .clk(clk),
        .reset(reset)
    );
    
    decode_unit #(
        .INSTR_WIDTH(INSTR_WIDTH)
    ) decode (
        .opcode_type(opcode_type),
        .opcode_group(opcode_group),
        .instruction(instr_buffer)
    );

    reg_file_interface_unit #(
        .DATA_WIDTH(DATA_WIDTH),
        .INSTR_WIDTH(INSTR_WIDTH),
        .D_ADDR_WIDTH(D_ADDR_WIDTH),
        .R_ADDR_WIDTH(R_ADDR_WIDTH)
    ) rf_int (
        .state(state),
        .opcode_type(opcode_type),
        .instruction(instr_buffer),
        .writeback_value(writeback_value),
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

    bus_interface_unit #(
        .DATA_WIDTH(DATA_WIDTH),
        .INSTR_WIDTH(INSTR_WIDTH),
        .D_ADDR_WIDTH(D_ADDR_WIDTH)
    ) bus_int (
        .state(state),
        .opcode_type(opcode_type),
        .instruction(instruction),
        .mem_addr(mem_addr),
        .mem_data(mem_data),
        .mem_cs(mem_cs),
        .mem_we(mem_we),
        .mem_oe(mem_oe),
        .indirect_addr(indirect_addr),
        .data_to_write(data_to_write_to_mem)
    );

    /* TODO: ce se scrie in memoria ram */
    assign data_to_write_to_mem = {DATA_WIDTH{1'bx}};

    /* TODO: ce se scrie in registrii */
    assign writeback_value = 
        (opcode_group == `GROUP_ARITHMETIC) ? alu_out_buffer : 
		  (opcode_type == `TYPE_LDI ? {instruction[12:9],instruction[3:0]} : {DATA_WIDTH{1'bz}});

	 /* TODO: adresare indirecta */
    assign indirect_addr = {DATA_WIDTH{1'bz}};
          
    assign alu_flags_in = sreg;
    /* Bloc de atribuire al sreg-ului */
    always @(posedge clk)
        if (reset)
            sreg <= 0;
        else if (alu_enable) begin
            sreg <= alu_flags_out;
            $display("Status register is now: I-%d T-%d H-%d S-%d V-%d N-%d Z-%d C-%d",
                     alu_flags_out[7], alu_flags_out[6], alu_flags_out[5], alu_flags_out[4],
                     alu_flags_out[3], alu_flags_out[2], alu_flags_out[1], alu_flags_out[0]);
        end

    /* Bloc de atribuire al program counter-ului */
    always @(posedge clk) begin
        if (reset) begin
            program_counter <= 0;
            $display("Resetting program counter to 0");
        end else if (state == `STATE_WB) begin
            program_counter <= program_counter + 1;
            $display("Program counter is now at: %2d", program_counter + 1);
        end
    end

    /* Buffer pentru instructiunea citita */
    always @(posedge clk)
        if (state == `STATE_IF)
            instr_buffer <= instruction;

    /* Buffer pentru output-ul UAL-ului */
    always @(posedge clk)
        if (state == `STATE_EX)
            alu_out_buffer <= alu_out;

    /* Buffer pentru rd_data si rr_data */
    always @(posedge clk)
        if (state == `STATE_ID) begin
            alu_rd <= rd_data;
            alu_rr <= rr_data;
        end
     
    assign alu_enable = (state == `STATE_EX) &&
                        (opcode_group == `GROUP_ARITHMETIC);
    /* Set alu_opsel to appropriate operation,
     * according to opcode_type and alu_enable */
    always @* begin
        if (alu_enable == 0)
            alu_opsel = 8'bz;
        else begin
            case (opcode_type)
            `TYPE_ADD:
                alu_opsel = `OPSEL_ADD;
            `TYPE_SUB:
                alu_opsel = `OPSEL_SUB;
            `TYPE_AND:
                alu_opsel = `OPSEL_AND;
            `TYPE_EOR:
                alu_opsel = `OPSEL_XOR;
            `TYPE_OR:
                alu_opsel = `OPSEL_OR;
            `TYPE_NEG:
                alu_opsel = `OPSEL_NEG;
            default:
                alu_opsel = 0;
            endcase
        end
    end

endmodule
