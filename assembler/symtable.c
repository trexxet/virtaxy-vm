// Symbol table types & functions

#include "symtable.h"
#include <string.h>
#include <stdlib.h>


_ERRNO_T symInit(symTable *S)
{
	S->size = 0;
	S->maxSize = INIT_PROGRAM_SIZE;
	return (S->sym = calloc(INIT_PROGRAM_SIZE, sizeof(symbol))) ? SUCCESS : CANNOT_ALLOCATE_MEMORY;
}


void symAdd(symTable *S, char *name, int64_t value)
{
	// Check symbol table size
	if (S->maxSize - S->size < 1)
		S->sym = (symbol *) realloc(S->sym, (S->maxSize += S->maxSize / 2) * sizeof(symbol));
	strcpy(S->sym[S->size].name, name);
	S->sym[S->size].value = value;
	S->size++;
}


int symGetValue(symTable *S, char *name, int64_t *value)
{
	for (uint64_t i = 0; i < S->size; i++)
		if (strcmp(S->sym[i].name, name) == 0)
		{
			if (value)
				*value = S->sym[i].value;
			return i;
		}
	return -1;
}


void symDestroy(symTable *S)
{
	free(S->sym);
}


// Debug
#include <stdio.h>
void symPrint(symTable *S)
{
	fprintf(stderr, "===SYMBOL TABLE===\n");
	for (int i = 0; i < S->size; i++)
		fprintf(stderr, "\t'%s': %-48lld\n", S->sym[i].name, S->sym[i].value);
}

