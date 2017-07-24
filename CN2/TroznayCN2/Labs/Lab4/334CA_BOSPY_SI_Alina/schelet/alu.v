`include "defines.vh"
module alu #(
        parameter DATA_WIDTH = 8
    )(
        input  wire [7:0]            opsel,
        input  wire                  enable,
        input  wire [DATA_WIDTH-1:0] rd,
        input  wire [DATA_WIDTH-1:0] rr,
        output reg  [DATA_WIDTH-1:0] out,
        input  wire [7:0]            flags_in,
        output reg  [7:0]            flags_out
    );

    always @* begin
        if (enable)
            case (opsel)
            `OPSEL_ADD: 
				begin
                    $display("Executing ADD operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rd + rr;
                    $display("ADD operation completed with result: %2d", out);
            end
            `OPSEL_SUB: 
				begin
                    $display("Executing SUB operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rd - rr;
                    $display("SUB operation completed with result: %2d", out);
            end	
            `OPSEL_AND: 
				begin
                    $display("Executing AND operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rd & rr;
                    $display("AND operation completed with result: %2d", out);
            end
            `OPSEL_XOR: 
				begin
                    $display("Executing XOR operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rd ^ rr;
                    $display("XOR operation completed with result: %2d", out);
            end
            `OPSEL_OR: 
				begin
                    $display("Executing OR operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rd | rr;
                    $display("OR operation completed with result: %2d", out);
            end
            `OPSEL_NEG: 
				begin
                    $display("Executing NEG operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = ~rd;
                    $display("NEG operation completed with result: %2d", out);
            end
            `OPSEL_NONE: 
				begin
                    $display("Executing NONE operation! Operands are: RR - %2d, RD - %2d", rr, rd);
                out = rr;
                    $display("NONE operation completed with result: %2d", out);
            end
            /* Pentru a evita generarea unui latch, flags_out
             * trebuie sa ia o valoare si aici. Este de datoria noastra
             * sa nu salvam aceasta valoare in control_unit */
            default: begin
                out = {DATA_WIDTH{1'bx}};
                flags_out = 8'bx;
            end
            endcase
        else /* if alu_enable == false */ begin
            out = {DATA_WIDTH{1'bz}};
            flags_out = 8'bz;
        end
    end

endmodule
