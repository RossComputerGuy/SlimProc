module cpu_fetch(input wire clk,
	input wire rst,
	input wire [31:0] fetch_addr,
	output wire [31:0] fetch_data,
	output wire [7:0] ivt_no,
	output wire is_intr);
endmodule
