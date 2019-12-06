cmake_minimum_required(VERSION 3.15)
project(slimproc-fpga NONE)

find_program(IVERILOG NAMES iverilog)

set(SOURCES "${PROJECT_SOURCE_DIR}/src/cpu/alu.v" "${PROJECT_SOURCE_DIR}/src/cpu/control-unit.v"
	"${PROJECT_SOURCE_DIR}/src/cpu/datapath-unit.v" "${PROJECT_SOURCE_DIR}/src/cpu/regs.v")
add_custom_target(fpga-soc ALL
	COMMAND ${IVERILOG} -o "${PROJECT_BINARY_DIR}/fpga-soc" -I "${PROJECT_SOURCE_DIR}/include" ${SOURCES}
	SOURCES "${SOURCES}")