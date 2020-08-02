#include <stdlib.h>
#include <string.h>
#include "instr.h"


int instr_compar(const void* i1, const void* i2)
{
	instr_t* instr1 = (instr_t*) i1;
	instr_t* instr2 = (instr_t*) i2;
	return strcmp(instr1->str, instr2->str);
}


instr_t* getInstr(const char* str, const instr_t* instrTable, size_t instrTableSize)
{
	const instr_t key = {.str = str, .encoder = NULL};
	return bsearch(&key, instrTable, instrTableSize, sizeof(instr_t), instr_compar);
}

int isInstr(const char* str, const instr_t* instrTable, size_t instrCount)
{
	return (int) (getInstr(str, instrTable, instrCount) != NULL);
}

