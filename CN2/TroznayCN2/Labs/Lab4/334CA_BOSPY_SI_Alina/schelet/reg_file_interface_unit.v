`include "defines.vh"
module reg_file_interface_unit #(
        parameter INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter DATA_WIDTH   = 8,    // registers are 8 bits in width
        parameter D_ADDR_WIDTH = 7,    // 128 bytes of SRAM
        parameter R_ADDR_WIDTH = 5     // 32 registers 
    )(
        input  wire [2:0]              state,
        input  wire [7:0]              opcode_type,
        input  wire [INSTR_WIDTH-1:0]  instruction,
        input  wire [DATA_WIDTH-1:0]   writeback_value,
        output wire [R_ADDR_WIDTH-1:0] rr_addr,
        output wire [R_ADDR_WIDTH-1:0] rd_addr,
        inout  wire [DATA_WIDTH-1:0]   rr_data,
        inout  wire [DATA_WIDTH-1:0]   rd_data,
        output wire                    rr_cs,
        output wire                    rd_cs,
        output wire                    rr_we,
        output wire                    rd_we,
        output wire                    rr_oe,
        output wire                    rd_oe
    );

	 /* Instructiuni executate pe UAL */
    wire opc_alu;
	 
	 /* Instructiuni aritmetice cu 2 operanzi */
    wire opc_alu_twoop;
	 
	 /* Instructiuni aritmetice cu 1 operand */
    wire opc_alu_oneop;
	 
	 /* Instructiuni care lucreaza cu memoria */
    wire opc_mem;
	 
	 /* Instructiuni care lucreaza cu registrii */
    wire opc_reg;
	 
	 /* Instructiuni care scriu inapoi in registrii */
    wire should_writeback;
	 
	 /* Instructiuni care folosesc registrul Rd */
    wire should_read_rd;
	 
	 /* Instructiuni care folosesc registrul Rr */
    wire should_read_rr;
	 
    wire [R_ADDR_WIDTH-1:0] rr_address;
    wire [R_ADDR_WIDTH-1:0] rd_address;

    /* Unele asignarile de mai jos presupun ca instructiunea
     * curenta (instruction) este de tipul:
     * [opcode] Rd Rr,
     * caz in care va accesa de doua ori register file-ul:
     * o data in starea de instruction decode/register fetch,
     * pentru a citi valorile ambelor registre, si a doua oara
     * in write-back, pentru a depune rezultatul (alu_out) in
     * registrul Rd.
     * Evident, nu toate instructiunile sunt de acest tip.
     * Unele instructiuni (spre exemplu load-urile) nu acceseaza
     * deloc register file-ul pentru citire, doar pentru write-back.
     * Altele, precum store-urile, il acceseaza doar pentru citire.
     * Altele, precum mov-ul, il acceseaza si pentru citire si
     * pentru scriere, dar citirea o fac din Rr si scrierea in Rd.
     * Altele nu il acceseaza deloc.
     * In concluzie, adaugati in conditiile assign-urilor si tipul
     * instructiunii (opcode_type si/sau instruction).
     */
    assign opc_alu       = opc_alu_oneop || opc_alu_twoop;
    assign opc_alu_oneop = (opcode_type == `TYPE_NEG);
    assign opc_alu_twoop = (opcode_type == `TYPE_ADD) ||
                           (opcode_type == `TYPE_ADC) ||
                           (opcode_type == `TYPE_AND) ||
                           (opcode_type == `TYPE_SUB) ||
                           (opcode_type == `TYPE_EOR) ||
                           (opcode_type == `TYPE_OR)  ||
									(opcode_type == `TYPE_LDI) ||
									(opcode_type == `TYPE_LDS);
									
	 /* TODO: completati cu instructiunile ce folosesc registrii */
    assign opc_reg = (opcode_type == `TYPE_ADD) ||
							(opcode_type == `TYPE_ADC) ||
							(opcode_type == `TYPE_AND) ||
							(opcode_type == `TYPE_SUB) ||
							(opcode_type == `TYPE_EOR) ||
							(opcode_type == `TYPE_OR)  ||
							(opcode_type == `TYPE_LDI) ||
							(opcode_type == `TYPE_LDS);
							
    /* TODO: completati cu instructiunile ce folosesc memoria ram */
    assign opc_mem = opcode_type == `TYPE_LDS;

    /* TODO: faceti modificarile necesare pentru a asigura functionarea
	 corecta a instructiunilor MOV, LDS, LDD, LDI, STS */
    assign should_writeback = (state == `STATE_WB) && 
		(opc_alu || opcode_type == `TYPE_LDI || opcode_type == `TYPE_LDS);
										
    assign should_read_rr = (state == `STATE_ID || state == `STATE_EX) &&
                            (opc_alu_twoop);
									 
    assign should_read_rd = (state == `STATE_ID || state == `STATE_EX) &&
                            (opc_alu);

    assign rd_address = {1'b1, instruction[7:4]};
    assign rr_address = {1'b1, instruction[3:0]};

    assign rd_data = should_writeback ? writeback_value : {DATA_WIDTH{1'bz}};
    assign rr_data = {DATA_WIDTH{1'bz}};
	 
    assign rd_we   = should_read_rd ? 0 : should_writeback ? 1 : 1'bz;
    assign rr_we   = should_read_rr ? 0 : 1'bz;
    
	 assign rd_oe   = should_read_rd ? 1 : 1'bz;
    assign rr_oe   = should_read_rr ? 1 : 1'bz;
    
	 assign rr_cs   = should_read_rr;
    assign rd_cs   = should_read_rd || should_writeback;
    
	 assign rd_addr = (rd_cs) ? rd_address : {DATA_WIDTH{1'bz}};
    assign rr_addr = (rr_cs) ? rr_address : {DATA_WIDTH{1'bz}};
	 
	 // end of TODO
	 
endmodule
