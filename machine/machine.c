#define _GNU_SOURCE

#include <stdlib.h>
#include <stdint.h>

#include "mem.h"
#include "errors.h"
#include "machine.h"


mem_t M;


_ERRNO_T machineInit(size_t memSize) {
	return memInit(&M, memSize);
}


_ERRNO_T machineRun() {
	return SUCCESS;
}


void machineDestroy() {
	memDestroy(&M);
}

