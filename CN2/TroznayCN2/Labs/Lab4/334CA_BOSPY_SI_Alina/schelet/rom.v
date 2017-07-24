module rom #(
        parameter   DATA_WIDTH = 16,
        parameter   ADDR_WIDTH = 8 
    )(
        input  wire [ADDR_WIDTH-1:0] addr,  // here comes the program counter
        output wire [DATA_WIDTH-1:0] data   // here goes the instruction
    );

    reg [DATA_WIDTH-1:0] value;

    /* TODO: de scris niste instructiuni valide */
    always @* begin
        case (addr)
        /* ldi R19, 69      => R19 = 69 */
        0:          value = 16'b1110_0100_0011_0101;
		  1:			  value = 16'b1010_0000_0011_0001;
        default:    value = 0;
        endcase
    end
        
    assign data = value;

endmodule
