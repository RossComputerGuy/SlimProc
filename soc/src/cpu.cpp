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
						// TODO: overflow
					} else if (wrote == -1 || wrote == -2) {
						// TODO: error code
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
						// TODO: overflow
					} else if (wrote == -1 || wrote == -2) {
						// TODO: error code
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
						// TODO: overflow
					} else if (wrote == -1 || wrote == -2) {
						// TODO: error code
					}
				}
			}
			break;
		case INST_DIV:
			{
				if (regread(op2) == 0) {
					// TODO: handle division by zero
				}
				unsigned long res = regread(op1) / regread(op2);
				unsigned long wrote = regwrite(dest, res);
				if (wrote != res) {
					if (wrote < res && wrote >= 0) {
						// TODO: overflow
					} else if (wrote == -1 || wrote == -2) {
						// TODO: error code
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
						// TODO: overflow
					} else if (wrote == -1 || wrote == -2) {
						// TODO: error code
					}
				}
			}
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