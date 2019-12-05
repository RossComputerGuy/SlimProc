#include <slimproc/cpu.h>
#include <soc/cpu.h>

void cpu::step() {
/** Fetch and "decode" **/
	sc_uint<32> curr_pc(pc);
	mmu_addr.write(curr_pc);
	mmu_read.write(true);
	wait(read_delay);
	sc_uint<32> opcode(mmu_read);

	pc++;
	mmu_addr.write(curr_pc);
	mmu_read.write(true);
	wait(read_delay);
	sc_uint<32> dest(mmu_read);

	pc++;
	mmu_addr.write(curr_pc);
	mmu_read.write(true);
	wait(read_delay);
	sc_uint<32> op1(mmu_read);
	
	pc++;
	mmu_addr.write(curr_pc);
	mmu_read.write(true);
	wait(read_delay);
	sc_uint<32> op2(mmu_read);

/** Execute **/
	switch (opcode) {
		case INST_NOP: break;
		case INST_ADD:
			{
				unsigned long res = regread(op1) + regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_SUB:
			{
				unsigned long res = regread(op1) - regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_MUL:
			{
				unsigned long res = regread(op1) * regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_DIV:
			{
				if (regread(op2) == 0) {
					interrupt(IVT_DIV_BY_ZERO);
					break;
				}
				unsigned long res = regread(op1) / regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_MOD:
			{
				unsigned long res = regread(op1) % regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_AND:
			{
				unsigned long res = regread(op1) & regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_OR:
			{
				unsigned long res = regread(op1) | regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_XOR:
			{
				unsigned long res = regread(op1) ^ regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_NOT:
			{
				unsigned long res = ~regread(op1);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_LSHF:
			{
				unsigned long res = regread(op1) << regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_RSHF:
			{
				unsigned long res = regread(op1) >> regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						interrupt(IVT_OVERFLOW);
					} else if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_LT:
			{
				unsigned long res = regread(op1) < regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_GT:
			{
				unsigned long res = regread(op1) > regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_EQ:
			{
				unsigned long res = regread(op1) == regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
					}
				}
			}
			break;
		case INST_JEQ:
			if (regread(dest) == op1) pc = op2;
			break;
		case INST_JNEQ:
			if (regread(dest) != op1) pc = op2;
			break;
		case INST_LOAD:
			mmu_value.write(regread(dest));
			mmu_read.write(true);
			wait(read_delay);
			break;
		case INST_STORE:
			{
				mmu_addr.write(op1);
				mmu_read.write(true);
				wait(read_delay);
				sc_uint_base res(mmu_data);
				sc_uint<32> wrote(regwrite(dest, res));
				if (wrote != mmu_data) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
						break;
					}
				}
			}
			break;
		case INST_SET:
			{
				sc_uint<32> wrote(regwrite(dest, op1));
				if (wrote != op1) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
						break;
					}
				}
			}
			break;
		case INST_JMP:
			pc = op1;
			break;
		case INST_RET:
			pc = stack_pop();
			break;
		case INST_CALL:
			stack_push(pc);
			pc = regread(op1);
			break;
		case INST_PUSH:
			stack_push(regread(op1));
			break;
		case INST_POP:
			{
				unsigned long res = stack_pop();
				unsigned long wrote = regwrite(dest, res);
				if (res != wrote) {
					if (wrote == -1 || wrote == -2) {
						interrupt(wrote == -1 ? IVT_PROTECTION : IVT_UNKNOWN_OPCODE);
						break;
					}
				}
			}
			break;
		case INST_IRET:
			loadregs(&intr_regs);
			is_int = false;
			break;
		case INST_INT:
			interrupt(regread(op1));
			break;
		case INST_LDIVT:
			ivt_addr = regread(op1);
			break;
	}
}

unsigned long cpu::regwrite(int reg, unsigned long data) {
	switch (reg) {
		case REG_PC:
		case REG_FLAGS:
			return -1;
		case REG_SKPTR:
			reg_skptr = data;
			return reg_skptr;
		case REG_ADDR0:
			reg_addr0 = data;
			return reg_addr0;
		case REG_ADDR1:
			reg_addr1 = data;
			return reg_addr1;
		case REG_ADDR2:
			reg_addr2 = data;
			return reg_addr2;
		case REG_ADDR3:
			reg_addr3 = data;
			return reg_addr3;
		case REG_ADDR4:
			reg_addr4 = data;
			return reg_addr4;
		case REG_ADDR5:
			reg_addr5 = data;
			return reg_addr5;
		default: return -2;
	}
	return 0;
}

unsigned long cpu::regread(int reg) {
	switch (reg) {
		case REG_PC: return pc;
		case REG_FLAGS: return getflags();
		case REG_SKPTR: return reg_skptr;
		case REG_ADDR0: return reg_addr0;
		case REG_ADDR1: return reg_addr1;
		case REG_ADDR2: return reg_addr2;
		case REG_ADDR3: return reg_addr3;
		case REG_ADDR4: return reg_addr4;
		case REG_ADDR5: return reg_addr5;
	}
	return 0;
}

int cpu::interrupt(int i) {
	sc_uint<8 * IVT_SIZE> ivt_bytes;
	for (int i = 0; i < IVT_SIZE; i++) {
		mmu_addr.write(ivt_addr + i);
		mmu_read.write(true);
		wait(read_delay);
		ivt_bytes.range(i, i + 8) = mmu_data;
	}

	unsigned int length = ivt_bytes.range(0, 7);
	if (length < i) return -1;

	unsigned long addr_intr = ivt_bytes.range(8 + (i * 32), 8 + (i * 32) + 31);
	saveregs(&intr_regs);

	is_int = true;
	reg_addr0 = i;
	return 0;
}

unsigned int cpu::getflags() {
	unsigned int flags = 0;
	if (is_int) flags |= FLAG_INTING;
	return flags;
}

void cpu::setflags(unsigned int flags) {
	is_int = flags & FLAG_INTING == FLAG_INTING;
}

void cpu::saveregs(regs_t* regs) {
	regs->pc = pc;
	regs->flags = getflags();
	regs->addr[0] = reg_addr0;
	regs->addr[1] = reg_addr1;
	regs->addr[2] = reg_addr2;
	regs->addr[3] = reg_addr3;
	regs->addr[4] = reg_addr4;
	regs->addr[5] = reg_addr5;
}

void cpu::loadregs(regs_t* regs) {
	pc = regs->pc;
	setflags(regs->flags);
	reg_addr0 = regs->addr[0];
	reg_addr1 = regs->addr[1];
	reg_addr2 = regs->addr[2];
	reg_addr3 = regs->addr[3];
	reg_addr4 = regs->addr[4];
	reg_addr5 = regs->addr[5];
}

void cpu::stack_push(unsigned long value) {
	if (is_int) {
		ivt_stack.range(ivt_stackidx, ivt_stackidx + 7) = value;
		ivt_stackidx += 7;
	} else if (reg_skptr == 0) {
		stack.range(stackidx, stackidx + 7) = value;
		stackidx += 7;
	}
}

unsigned long cpu::stack_pop() {
	if (is_int) {
		unsigned long value = ivt_stack.range(ivt_stackidx, ivt_stackidx + 7);
		ivt_stackidx -= 7;
		return value;
	}
	if (reg_skptr == 0) {
		unsigned long value = stack.range(stackidx, stackidx + 7);
		stackidx -= 7;
		return value;
	}
	return 0;
}