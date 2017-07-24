`include "defines.vh"
module decode_unit #(
        parameter  INSTR_WIDTH  = 16   // instructions are 16 bits in width
    )(
        input wire [INSTR_WIDTH-1:0] instruction,
        output reg [7:0]             opcode_type,
        output reg [7:0]             opcode_group
    );

    always @* begin
        case (instruction[15:0])
        16'b000000000000:
            /* nop: 0000 0000 0000 0000 */
            opcode_type = `TYPE_NOP;
        default: begin
            /* 11 bit opcode */
            case ({instruction[15:9], instruction[3:0]})
            default: begin
                /* 8 bit opcode */
                case (instruction[15:8])
                8'b00001111:
                    /* add: 0000 11rd dddd rrrr */
                    opcode_type = `TYPE_ADD;
                8'b00011111:
                    /* adc: 0001 11rd dddd rrrr */
                    opcode_type = `TYPE_ADC;
                default: begin
                    /* 7 bit opcode */
                    case (instruction[15:9])
                    7'b1001010:
                        /* neg: 1001 010d dddd 0001 */
                        opcode_type = `TYPE_NEG;
						  7'b1000000:
								/* ldd: 1000 000d dddd 1000 */
								opcode_type = `TYPE_LDD;
                    default: begin
                        /* 6 bit opcode */
                        case (instruction[15:10])
                        6'b00100:
                            /* and: 0010 00rd dddd rrrr */
                            opcode_type = `TYPE_AND;
                        6'b001010:
                            /* or: 0010 10rd dddd rrrr */
                            opcode_type = `TYPE_OR;
                        6'b001001:
                            /* eor: 0010 01rd dddd rrrr */
                            opcode_type = `TYPE_EOR;
                        6'b000110:
                            /* sub: 0001 10rd dddd rrrr */
                            opcode_type = `TYPE_SUB;
								6'b001011:
									 /* mov: 0010 11rd dddd rrrr */
									 opcode_type = `TYPE_MOV;
                        default: begin
									case(instruction[15:11])
									5'b10100:
										/* lds: 1010 0kkk dddd kkkk */
										opcode_type = `TYPE_LDS;
									5'b10101:
										/* sts: 1010 1kkk dddd kkkk */
										opcode_type = `TYPE_STS;
									default: begin
										case(instruction[15:12])
										4'b1110:
											/* ldi: 1110 kkkk dddd kkkk */
											opcode_type = `TYPE_LDI;
										default:	begin
												opcode_type = `TYPE_UNKNOWN;
										end
										endcase /* end 4 bits */
									end
									endcase /* end 5 bits */
								end
								endcase /* end 6 bits */
                    end
                    endcase /* end 7 bits */
                end
                endcase /* end 8 bits */
            end
            endcase /* end 11 bits */
        end
        endcase /* end 16 bits */
    end

    always @*
        case (opcode_type)
        `TYPE_ADD, `TYPE_ADC, `TYPE_SUB, `TYPE_AND, `TYPE_EOR, `TYPE_OR:
            opcode_group = `GROUP_ARITHMETIC;
        `TYPE_LDD, `TYPE_LDS, `TYPE_STS:
            opcode_group = `GROUP_MEMORY;
        `TYPE_MOV, `TYPE_LDI:
            opcode_group = `GROUP_REGISTER;
        default:
            opcode_group = `GROUP_DEFAULT;
        endcase
endmodule
