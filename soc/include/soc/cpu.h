#pragma once

#include <slimproc/cpu.h>
#include <systemc.h>

struct cpu : sc_module {
	sc_out<sc_uint<32>> mmu_addr;
	sc_out<bool> mmu_read;
	sc_out<bool> mmu_write;
	sc_in<sc_uint<32>> mmu_data;
	int read_delay;

	sc_out<bool> reset;
	sc_in_clk CLK;

	int is_int:2;
	sc_uint<8> intno;
	sc_uint<32> pc;

	sc_uint<32> reg_skptr;
	sc_uint<32> reg_addr0;
	sc_uint<32> reg_addr1;
	sc_uint<32> reg_addr2;
	sc_uint<32> reg_addr3;
	sc_uint<32> reg_addr4;
	sc_uint<32> reg_addr5;

	sc_uint<32 * STACK_SIZE> stack;
	unsigned int stackidx;

	sc_uint<32 * STACK_SIZE> ivt_stack;
	unsigned int ivt_stackidx;
	sc_uint<32> ivt_addr;
	regs_t intr_regs;

	void step();

	unsigned long regwrite(int reg, unsigned long data);
	unsigned long regread(int reg);

	int interrupt(int i);

	unsigned int getflags();
	void setflags(unsigned int flags);

	void saveregs(regs_t* regs);
	void loadregs(regs_t* regs);

	void stack_push(unsigned long value);
	unsigned long stack_pop();
};
