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
int debug = 0;
#include <stdio.h>
void dumpRegisters();
void dumpEverything();
#define dumpCmd() printf("op = %llx\targ1 = %lld\targ2 = %lld\targ3 = %lld\n", opcode, arg1, arg2, arg3);


_ERRNO_T machineInit(size_t memSize) {
	WRITE_REG(BP, memSize - 1);
	WRITE_REG(SP, memSize - 1);
	return memInit(&M, memSize);
}


_ERRNO_T machineRun() {
	while (1) {
		int64_t opcode = READ_MEM(READ_REG(IP));
		int64_t arg1 = READ_MEM(READ_REG(IP)+1);
		int64_t arg2 = READ_MEM(READ_REG(IP)+2);
		int64_t arg3 = READ_MEM(READ_REG(IP)+3);

		if (debug) {
			dumpRegisters();
			dumpCmd();
		}

		switch (opcode)
		{
			#include "machine_generated.c"
		}
	}

stop:
	return SUCCESS;
}


void machineDestroy() {
	memDestroy(&M);
}


void dumpEverything() {
	dumpRegisters();
	memDump(&M);
}


void dumpRegisters() {
	for (int i = 0; i < NUM_OF_REGNAMES; i++)
	{
		printf("%s: %lld\t", regTable[i].name, READ_REG(i));
		if ((i + 1) % 7 == 0)
			printf("\n");
	}
	printf("\n");
}

