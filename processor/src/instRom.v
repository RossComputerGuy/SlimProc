module instRom (input address[16], output inst[55]) {
	always {
		inst = c{Inst.NOP, 47b0};
	}
}
