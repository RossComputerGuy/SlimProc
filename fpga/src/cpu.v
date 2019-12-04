global Inst {
	const NOP = 8d0; // No operation

	// Mathematical operations
	const ADD = 8d1; // dest, op1, op2: R[dest] = R[op1] + R[op2]
	const SUB = 8d2; // dest, op1, op2: R[dest] = R[op1] - R[op2]
	const MUL = 8d3; // dest, op1, op2: R[dest] = R[op1] * R[op2]
	const DIV = 8d4; // dest, op1, op2: R[dest] = R[op1] / R[op2]
	const MOD = 8d5; // dest, op1, op2: R[dest] = R[op1] % R[op2]
	const AND = 8d6; // dest, op1, op2: R[dest] = R[op1] & R[op2]
	const OR = 8d7; // dest, op1, op2: R[dest] = R[op1] | R[op2]
	const XOR = 8d8; // dest, op1, op2: R[dest] = R[op1] ^ R[op2]
	const NOT = 8d9; // dest, op1: R[dest] = ~R[op1]
	const LSHF = 8d10; // dest, op1, op2: R[dest] = R[op1] << R[op2]
	const RSHF = 8d11; // dest, op1, op2: R[dest] = R[op1] >> R[op2]

	// Logic operations
	const LT = 8d12; // dest, op1, op2: R[dest] = R[op1] < R[op2]
	const GT = 8d13; // dest, op1, op2: R[dest] = R[op1] > R[op2]
	const EQ = 8d14; // dest, op1, op2: R[dest] = R[op1] == R[op2]
	const JEQ = 8d15; // op1, const: R[0] = R[0] + (R[op1] == const ? 2 : 1)
	const JNEQ = 8d16; // op1, const: R[0] = R[0] + (R[op1] != const ? 2 : 1)

	// I/O operations
	const LOAD = 8d17; // dest, op1, offset: R[dest] = M[R[op1] + offset]
	const STORE = 8d18; // dest, op1, offset: M[R[dest] + offset] = R[dest]
	const SET = 8d19; // dest, op1: R[dest] = op1
}

global Reg {
	const PC = 0; // Program counter
	const FLAGS = 1; // CPU flags
}

module cpu (input clk, input rst, output write, output read, output address[32], output dout[32], input din[32]) {
	.clk(clk), .rst(rst) {
		dff reg[32][32];
	}

	instRom instRom;

	sig op[8];
	sig arg1[16];
	sig arg2[16];
	sig dest[16];
	sig constant[8];
  // TODO: add stack

	always {
		write = 0;
		read = 0;
		address = 32hxx;
		dout = 32hxx;

		instRom.address = reg.q[Reg.PC];
		reg.d[Reg.PC] = reg.q[Reg.PC] + 1;

		op = instRom.inst[98:95];
		dest = instRom.inst[94:63];
		arg1 = instRom.inst[61:32];
		arg2 = instRom.inst[31:0];
		constant = instRom.inst[7:0];

		// Execute
		case (op) {
			// Mathematical operations
			Inst.ADD:
				reg.d[dest] = reg.q[arg1] + reg.q[arg2];
			Inst.SUB:
				reg.d[dest] = reg.q[arg1] - reg.q[arg2];
			Inst.MUL:
				reg.d[dest] = reg.q[arg1] * reg.q[arg2];
			Inst.DIV:
				reg.d[dest] = reg.q[arg1] / reg.q[arg2]; // TODO: add an interrupt vector table and handle a divsion by zero
			Inst.MOD:
				reg.d[dest] = reg.q[arg1] % reg.q[arg2];
			Inst.AND:
				reg.d[dest] = reg.q[arg1] & reg.q[arg2];
			Inst.OR:
				reg.d[dest] = reg.q[arg1] | reg.q[arg2];
			Inst.XOR:
				reg.d[dest] = reg.q[arg1] ^ reg.q[arg2];
			Inst.NOT:
				reg.d[dest] = ~reg.q[arg1];
			Inst.LSHF:
				reg.d[dest] = reg.q[arg1] << reg.q[arg2];
			Inst.RSHF:
				reg.d[dest] = reg.q[arg1] >> reg.q[arg2];

			// Logic operations
			Inst.LT:
				reg.d[dest] = reg.q[arg1] < reg.q[arg2];
			Inst.GT:
				reg.d[dest] = reg.q[arg1] > reg.q[arg2];
			Inst.EQ:
				reg.d[dest] = reg.q[arg1] == reg.q[arg2];
			Inst.JEQ:
				if (reg.q[dest] == constant) reg.d[Reg.PC] = reg.q[Reg.PC] + 2;
			Inst.JNEQ:
				if (reg.q[dest] != constant) reg.d[Reg.PC] = reg.q[Reg.PC] + 2;

			// I/O operations
			Inst.LOAD:
				read = 1;
				reg.d[dest] = din;
				address = req.q[arg1] + arg2;
			Inst.STORE:
				write = 1;
				dout = reg.q[dest];
				address = req.q[arg1] + arg2;
			Inst.SET:
				reg.d[dest] = constant;
		}
	}
}
