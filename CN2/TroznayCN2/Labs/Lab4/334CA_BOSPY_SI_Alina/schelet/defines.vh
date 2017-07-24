`define DEBUG
/* In order to disable implicit declaration of wires */
`default_nettype none

/* States for FSM */
`define STATE_IF            0
`define STATE_ID            1
`define STATE_EX            2
`define STATE_MEM           3
`define STATE_WB            4
`define STATE_RESET         5

/* Opcode types deduced by decoder */
`define TYPE_NOP            0
`define TYPE_ADD            1
`define TYPE_ADC            2
`define TYPE_NEG            3
`define TYPE_AND            4
`define TYPE_OR             5
`define TYPE_EOR            6
`define TYPE_SUB            7
`define TYPE_UNKNOWN        8
`define TYPE_LDD            9
`define TYPE_LDS            10
`define TYPE_STS            11
`define TYPE_LDI            12
`define TYPE_MOV            13

/* Opcode groups */
`define GROUP_ARITHMETIC    0
`define GROUP_REGISTER      1
`define GROUP_MEMORY        2
`define GROUP_CONTROL_FLOW  3
`define GROUP_DEFAULT       4

/* Operations permitted by ALU */
`define OPSEL_ADD           0
`define OPSEL_SUB           1
`define OPSEL_AND           2
`define OPSEL_XOR           3
`define OPSEL_OR            4
`define OPSEL_NEG           5
`define OPSEL_NONE          6
/* TODO: add more */

`define C 7
`define Z 6
`define N 5
`define V 4
`define S 3
`define H 2
`define T 1
`define I 0