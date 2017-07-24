`include "defines.vh"
module state_machine (
        output reg  [2:0] state,
        input  wire       clk,
        input  wire       reset
    );

    reg [2:0] next_state;

    always @(posedge clk)
        if (reset)
            state <= `STATE_RESET;
        else
            state <= next_state;
            
    always @* begin
        case (state)
        `STATE_RESET:
            next_state = `STATE_IF;
        `STATE_IF:
            next_state = `STATE_ID;
        `STATE_ID:
            next_state = `STATE_EX;
        `STATE_EX:
            next_state = `STATE_MEM;
        `STATE_MEM:
            next_state = `STATE_WB;
        `STATE_WB:
            next_state = `STATE_IF;
        /* Should never get here, but anyway */
        default:
            next_state = `STATE_RESET;
        endcase
    end

endmodule
