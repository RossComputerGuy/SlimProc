module cpu_datapathunit(input clk,
	input jump, reg_dst, reg_write, mem_read, mem_write, memtoreg, beq, bne,
	input [15:0] alu_opcode,
	output [7:0] opcode);
/** Program counter **/
	reg [31:0] pc;
	wire [31:0] next_pc, pc2;
	wire [31:0] instr;
/** Registers **/
	wire [2:0] reg_write_dest;
	wire [31:0] reg_write_data;
	wire [2:0] reg_read0_addr;
	wire [31:0] reg_read0_data;
	wire [2:0] reg_read1_addr;
	wire [31:0] reg_read1_data;
/** Memory **/
	wire [31:0] mem_read_data;
/** ALU **/
	wire [15:0] alu_opcode;
	wire [31:0] alu_output;
/** Flags **/
	wire zero_flag;

	/* TODO: read memory */

	assign reg_write_dest = (reg_dst == 1'b1) ? instr[28:26] : instr[31:29];
	assign reg_read0_addr = instr[16:8];
	assign reg_read1_addr = instr[25:17];

	cpu_regs reg_file (
		.clk(clk),
		.write_enable(reg_write),
		.write_dest(reg_write_dest),
		.write_data(reg_write_data),
		.read0_addr(reg_read0_addr),
		.read0_data(reg_read0_data),
		.read1_addr(reg_read1_addr),
		.read1_data(reg_read1_data)
	);

	assign reg_write_data = (memtoreg == 1'b1) ? mem_read_data : alu_output;
	assign opcode = instr[7:0];
endmodule