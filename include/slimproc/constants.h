#pragma once

#define REG_PC 0
#define REG_FLAGS 1

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

/** Descriptor table **/
typedef struct {
	unsigned long address;
	unsigned int length;
} desctbl_t;

/** IVT Entries **/
#define IVT_DIV0 0
#define IVT_OVR 1
