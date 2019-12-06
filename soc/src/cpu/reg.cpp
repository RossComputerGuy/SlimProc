#include <soc/cpu.hpp>

void cpu::set_reg(int reg, sc_uint<32> data) {
	switch (reg) {
		case REG_PC: throw CPU_ERROR_PERMISSION;
		case REG_FLAGS:
			break;
		case REG_ADDR0:
			this->reg_addr0 = data;
			break;
		case REG_ADDR1:
			this->reg_addr1 = data;
			break;
		case REG_ADDR2:
			this->reg_addr2 = data;
			break;
		case REG_ADDR3:
			this->reg_addr3 = data;
			break;
		case REG_ADDR4:
			this->reg_addr4 = data;
			break;
		case REG_ADDR5:
			this->reg_addr5 = data;
			break;
		default: throw CPU_ERROR_NO_REG;
	}
}

sc_uint<32> cpu::get_reg(int reg) {
	switch (reg) {
		case REG_PC: return this->reg_pc;
		case REG_FLAGS: return (this->is_intr ? FLAG_INTING : 0);
		case REG_ADDR0: return this->reg_addr0;
		case REG_ADDR1: return this->reg_addr1;
		case REG_ADDR2: return this->reg_addr2;
		case REG_ADDR3: return this->reg_addr3;
		case REG_ADDR4: return this->reg_addr4;
		case REG_ADDR5: return this->reg_addr5;
		default: throw CPU_ERROR_NO_REG;
	}
}
