#include "mem.h"
#include "config.h"
#include "errors.h"


_ERRNO_T memInit(mem_t *M, size_t memSize)
{
	M -> size = memSize;
	M -> data = (int64_t *) calloc(memSize, sizeof(int64_t));
	if (!M -> data)
		return CANNOT_ALLOCATE_MEMORY;
	return SUCCESS;
}


void memDestroy(mem_t *M)
{
	free(M -> data);
	M -> data = NULL;
	M -> size = 0;
}


// Debug
#include <stdio.h>
void memDump(mem_t *M)
{
	printf("\n===========================MEMORY DUMP==========================\n");
	for (size_t i = 0; i < M -> size; i++)
	{
		printf("%-8lx", M -> data[i]);
		if (((i + 1) & 0xF) == 0)
			printf("\n");
	}
	printf("\n=========================END OF MEM DUMP========================\n");
}

