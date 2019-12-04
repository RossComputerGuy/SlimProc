module instRom (input address[32], output inst[98]) {
	always {
		inst = c{Inst.NOP, 90b0};
	}
}
