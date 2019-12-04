global Inst {
	const NOP = 4d0; // No operation
	const ADD = 4d1; // dest, op1, op2: R[dest] = R[op1] + R[opt2]
}

module cpu (input clk, input rst, output write, output read, output address[16], output dout[8], input din[8]) {
	.clk(clk), .rst(rst) {
		dff reg[32][16];
	}

	instRom instRom;

	sig op[8];
	sig arg1[16];
	sig arg2[16];
	sig dest[16];
	sig constant[8];

	always {
		write = 0;
		read = 0;
		address = 32hxx;
		dout = 32hxx;

		instRom.address = reg.q[0];
		reg.d[0] = reg.q[0] + 1;

		op = instRom.inst[54:47];
		dest = instRom.inst[47:32];
		arg1 = instRom.inst[31:16];
		arg2 = instRom.inst[15:0];
		constant = instRom.inst[7:0];

		// Execute
		case (op) {
			Inst.ADD:
				reg.d[dest] = reg.q[arg1] + reg.q[arg2];
		}
	}
}
