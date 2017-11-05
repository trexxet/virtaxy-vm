#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "errors.h"


typedef struct {
	int64_t *data;
	size_t size;
} mem_t;


_ERRNO_T memInit(mem_t *M, size_t memSize);
void memDestroy(mem_t *M);
void memDump(mem_t *M);

