module led_game(
        input  wire       clk,
        input  wire       rst,
        output wire [7:0] led
    );
 
    wire [3:0] address;
    wire [7:0] data;
 
    fsm fsm1(
        .clk(clk),
        .rst(rst),
        .led(led),
        .address(address),
        .data(data)
    );
 
    rom rom1(
        .address(address),
        .data(data)
    );
 
endmodule