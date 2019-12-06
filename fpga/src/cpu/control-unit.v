module cpu_controlunit(input clk, reset, interrupt,
	input [7:0] opcode,
	output reg [15:0] alu_opcode,
	output reg jump, reg_dst, reg_write, mem_read, mem_write, memtoreg, beq, bne);
	always @(*)
	begin
		case (opcode)
			8'h0 /* NOP */:
				begin
					alu_opcode = 16'h11;
					jump = 1'h0;
					reg_write = 1'b0;
					mem_read = 1'b0;
					mem_write = 1'b0;
					memtoreg = 1'b0;
					reg_dst = 1'b0;
				end
			8'h1 /* ADD */:
				begin
					alu_opcode = 16'h0;
					jump = 1'h0;
					reg_write = 1'b1;
					memtoreg = 1'b0;
					reg_dst = 1'b1;
					beq = 1'b0;
					bne = 1'b0;
				end
		endcase
	end
endmodule