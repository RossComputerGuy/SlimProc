#pragma once

#include <slimproc/constants.h>
#include <systemc.h>

struct cpu : sc_module {
	sc_out<unsigned long> pc;
	sc_out<bool> reset;
	sc_in_clk CLK;

	int is_int:2;
	unsigned long intno;

	void step();

	unsigned int getflags();
	void setflags(unsigned int flags);

	void saveregs(regs_t* regs);
	void loadregs(regs_t* regs);
};
