#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>

#include "mem.h"
#include "registers.h"
#include "errors.h"
#include "machine.h"

#include "../common/generated/opcodes.h"
#include "vllm.h"


mem_t M;


// Debug
struct {int reg, mem, stack;} printDump = {0};
#include <stdio.h>
void dumpRegisters();
void dumpStack();
#define dumpCmd() printf("op = %llx\targ1 = %lld\targ2 = %lld\targ3 = %lld\n", opcode, arg1, arg2, arg3);


_ERRNO_T machineInit(size_t memSize) {
	// Init stack
	WRITE_REG(BP, memSize - 1);
	WRITE_REG(SP, memSize - 1);
	// Init memory
	return memInit(&M, memSize);
}


_ERRNO_T machineRun() {
	while (1) {
		// Fetch
		int64_t opcode = READ_MEM(READ_REG(IP));
		int64_t arg1 = READ_MEM(READ_REG(IP)+1);
		int64_t arg2 = READ_MEM(READ_REG(IP)+2);
		int64_t arg3 = READ_MEM(READ_REG(IP)+3);

		// Print debug dumps if needed
		if (printDump.reg) {
			dumpRegisters();
			dumpCmd();
		}
		if (printDump.mem)
			memDump(&M);
		if (printDump.stack)
			dumpStack();
		
		// Decode and execute
		switch (opcode)
		{
			#include "machine_generated.c"
			default:
				return UNKNOWN_COMMAND;
		}
	}

	stop:
	return SUCCESS;
}


void machineDestroy() {
	memDestroy(&M);
}


void dumpRegisters() {
	for (int i = 0; i < NUM_OF_REGNAMES; i++)
	{
		printf("%s: %llx\t\t", regTable[i].name, READ_REG(i));
		if ((i + 1) % 7 == 0)
			printf("\n");
	}
	printf("\n");
}

void dumpStack() {
	printf("\n===========================STACK DUMP===========================\n");
	for (size_t i = READ_REG(SP); i <= READ_REG(BP); i++)
		printf("%llx\n", M.data[i]);
	printf("========================END OF STACK DUMP=======================\n");
}

