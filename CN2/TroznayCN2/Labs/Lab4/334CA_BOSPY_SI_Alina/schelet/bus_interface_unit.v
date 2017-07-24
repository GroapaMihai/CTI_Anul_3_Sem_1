`include "defines.vh"
module bus_interface_unit #(
        parameter INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter DATA_WIDTH   = 8,    // registers are 8 bits in width
        parameter D_ADDR_WIDTH = 7     // 128 bytes of SRAM
    )(
        input  wire [2:0]              state,
        input  wire [7:0]              opcode_type,
        input  wire [INSTR_WIDTH-1:0]  instruction,
        input  wire [DATA_WIDTH-1:0]   data_to_write,
        input  wire [D_ADDR_WIDTH-1:0] indirect_addr,
        output wire [D_ADDR_WIDTH-1:0] mem_addr,
        inout  wire [DATA_WIDTH-1:0]   mem_data,
        output wire                    mem_cs,
        output wire                    mem_we,
        output wire                    mem_oe
    );

	 /* Instructiuni care acceseaza memoria */
    wire should_access_memory;
	 
	 /* Instructiuni care citesc din memorie */
    wire should_load;
	 
	 /* Instructiuni care scriu in memorie */
    wire should_store;
	 
	 /* Dimensiunea memoriei RAM */
    wire [D_ADDR_WIDTH-1:0] direct_addr;

	 /* TODO: Logica de interfatare a memoriei */
    assign should_load  = (opcode_type == `TYPE_LDS);//(opcode_type == `TYPE_LDI);
    assign should_store = 0;
    assign should_access_memory = should_store | should_load;
	 
	 /* TODO: setati mem_cs, mem_we, mem_oe, mem_addr si mem_data in functie de
	 should_load, should_store, should_access_memory si tipul instructiunilor */
		  
    /* Extras din datasheet pagina 96 */
    assign direct_addr = {~instruction[8], instruction[8],
                         instruction[10:9], instruction[3:0]};

endmodule
