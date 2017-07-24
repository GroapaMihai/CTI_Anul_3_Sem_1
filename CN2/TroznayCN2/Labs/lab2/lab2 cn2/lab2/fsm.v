`define DEBUG
 
module fsm (
`ifdef DEBUG
        output      [1:0] debug_state,
`endif
        input  wire clk,        // clock
        input  wire rst,        // reset
        output wire [7:0] led,
        output wire [3:0] address,
        input  wire [7:0] data
    );
 
    reg [1:0]  state;
    reg [1:0]  next_state;
    reg [7:0]  led_reg;
    reg [31:0] idle_counter;
	 reg [2:0] addressreg;
	 
	 assign address = addressreg;
 
    localparam STATE_IDLE = 0,
               STATE_MEM1 = 1,
               STATE_MEM2 = 2,
               // TODO:
               // Counter reference used by the prescaler state, IDLE.
               // This value may be too small. You might want to change it in 
               // ranges going from 0 to 5000000
               IDLE_COUNT = 5000000; 
 
    always @(posedge clk)
        if (rst)
            state = STATE_MEM1;
        else
            state = next_state;
 
    always @* begin
        case (state)
        STATE_MEM1:
		  begin
            // TODO: memory access code goes here
				addressreg = addressreg + 1;
				next_state = STATE_MEM2;
		  end
        STATE_MEM2:
		  begin
            // TODO: code for getting data from memory goes here
				led_reg = data;
            next_state = STATE_IDLE;
		  end
        STATE_IDLE:
            next_state = (idle_counter < IDLE_COUNT) ? STATE_IDLE : STATE_MEM1;
        endcase
    end
 
    always @(posedge clk)
        if (state == STATE_IDLE)
            idle_counter <= idle_counter + 1;
        else
            idle_counter <= 0;
 
    assign led = led_reg;
 
endmodule