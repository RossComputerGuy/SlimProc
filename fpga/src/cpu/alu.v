module cpu_alu(input [31:0] arg1,
	input [31:0] arg2,
	input [15:0] opcode,
	output reg [31:0] value);
	always @*
		case (opcode)
			15'h0 /* ADD */: value = arg1 + arg2;
			16'h1 /* SUB */: value = arg1 - arg2;
			16'h2 /* MUL */: value = arg1 * arg2;
			16'h3 /* DIV */: value = arg1 / arg2;
			16'h4 /* MOD */: value = arg1 % arg2;
			16'h5 /* AND */: value = arg1 & arg2;
			16'h6 /* OR */: value = arg1 | arg2;
			16'h7 /* XOR */: value = arg1 ^ arg2;
			16'h8 /* NOT */: value = ~arg1;
			16'h9 /* LSH */: value = arg1 << arg2;
			16'h10 /* RSH */: value = arg1 >> arg2;
			default: value = 0;
		endcase
endmodule