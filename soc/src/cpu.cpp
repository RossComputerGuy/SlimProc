#include <slimproc/constants.h>
#include <soc/cpu.h>

void cpu::step() {
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
	regs->pc = pc.read();
	regs->flags = getflags();
}

void cpu::loadregs(regs_t* regs) {
	pc.write(regs->pc);
	setflags(regs->flags);
}
