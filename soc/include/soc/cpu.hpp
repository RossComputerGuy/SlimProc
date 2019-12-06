#pragma once

#include <slimproc/cpu.h>
#include <soc/mmu.hpp>
#include <systemc.h>

#define CPU_ERROR_PERMISSION 1
#define CPU_ERROR_NO_REG 2

SC_MODULE(cpu) {
	public:
		mmu mem;
		SC_CTOR(cpu) : mem("cpu.mmu") {}

		virtual void push_stack(sc_uint<32> data);
		virtual sc_uint<32> pop_stack();

		virtual void set_reg(int reg, sc_uint<32> data);
		virtual sc_uint<32> get_reg(int reg);
	private:
		sc_uint<32> reg_pc;
		sc_uint<32> reg_addr0;
		sc_uint<32> reg_addr1;
		sc_uint<32> reg_addr2;
		sc_uint<32> reg_addr3;
		sc_uint<32> reg_addr4;
		sc_uint<32> reg_addr5;

		sc_uint<32 * STACK_SIZE> stack;
		uint32_t stack_index;

		sc_uint<32 * STACK_SIZE> intr_stack;
		uint32_t intr_stack_index;

		int is_intr:2;
	protected:
		virtual void step();
};
