module cpu_regs(input clk,
/** write **/
	input write_enable,
	input [2:0] write_dest,
	input [31:0] write_data,
/** read #1 **/
	input [2:0] read0_addr,
	output [31:0] read0_data,
/** read #2 **/
	input [2:0] read1_addr,
	output [31:0] read1_data);
	reg [31:0] reg_array [7:0];
	integer i;
	initial begin
		for (i = 0;i < 8; i = i+1) reg_array[i] <= 32'd0;
	end
	always @ (posedge clk ) begin
		if (write_enable) begin
			reg_array[write_dest] <= write_data;
		end
	end
	assign read0_data = reg_array[read0_addr];
	assign read1_data = reg_array[read1_addr];
endmodule