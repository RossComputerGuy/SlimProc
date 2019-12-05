#pragma once

#define REG_PC 0
#define REG_FLAGS 1
#define REG_SKPTR 2
#define REG_ADDR0 3
#define REG_ADDR1 4
#define REG_ADDR2 5
#define REG_ADDR3 6
#define REG_ADDR4 7
#define REG_ADDR5 8

#define NREG_ADDR (REG_ADDR5 - REG_ADDR0)

typedef struct {
	unsigned long pc;
	unsigned int flags;
	unsigned long addr[NREG_ADDR];
} __attribute__((packed)) regs_t;

#define STACK_SIZE (0x16000)

/** No operation **/
#define INST_NOP 0

/** Mathematical operations **/
#define INST_ADD 1
#define INST_SUB 2
#define INST_MUL 3
#define INST_DIV 4
#define INST_MOD 5
#define INST_AND 6
#define INST_OR 7
#define INST_XOR 8
#define INST_NOT 9
#define INST_LSHF 10
#define INST_RSHF 11

/** Logic operations **/
#define INST_LT 12
#define INST_GT 13
#define INST_EQ 14
#define INST_JEQ 15
#define INST_JNEQ 16

/** I/O operations **/
#define INST_LOAD 17
#define INST_STORE 18
#define INST_SET 19

/** Execution/stack operations */
#define INST_JMP 20
#define INST_RET 21
#define INST_CALL 22
#define INST_PUSH 23
#define INST_POP 24

/** Exceptions and interrupts **/
#define INST_IRET 25
#define INST_INT 26
#define INST_LDIVT 27

/** CPU Flag fields **/
#define FLAG_INTING 0

/** Descriptor table **/
#define IVT_SIZE (sizeof(unsigned int) + (sizeof(unsigned long) * 4))

/** IVT Entries **/
#define IVT_DIV_BY_ZERO 0
#define IVT_OVERFLOW 1
#define IVT_PROTECTION 2
#define IVT_UNKNOWN_OPCODE 3