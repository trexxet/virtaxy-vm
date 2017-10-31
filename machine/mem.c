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

