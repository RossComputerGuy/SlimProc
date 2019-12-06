#include <soc/cpu.hpp>

void cpu::step() {
/** Fetch **/
	sc_uint<32> opcode = this->mem.read(this->reg_pc++);
	sc_uint<32> dest = this->mem.read(this->reg_pc++);
	sc_uint<32> op1 = this->mem.read(this->reg_pc++);
	sc_uint<32> op2 = this->mem.read(this->reg_pc++);

/** Execute **/
}

void cpu::push_stack(sc_uint<32> data) {
	if (this->is_intr) {
		this->intr_stack.range(this->intr_stack_index * 32, (this->intr_stack_index * 32) + 32) = data;
		this->intr_stack_index++;
	} else {
		this->stack.range(this->stack_index * 32, (this->stack_index * 32) + 32) = data;
		this->stack_index++;
	}
}

sc_uint<32> cpu::pop_stack() {
	if (this->is_intr) {
		sc_uint<32> data = this->intr_stack.range(this->intr_stack_index * 32, (this->intr_stack_index * 32) + 32);
		this->intr_stack_index--;
		return data;
	}
	sc_uint<32> data = this->stack.range(this->stack_index * 32, (this->stack_index * 32) + 32);
	this->stack_index--;
	return data;
}
