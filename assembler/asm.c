#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "errors.h"
#include "config.h"

typedef char* string;

uint8_t* program;

_ERRNO_T asmInit()
{
	return (program = calloc(INIT_PROGRAM_SIZE, 1)) ? SUCCESS : CANNOT_ALLOCATE_MEMORY;
}

// Macros for assembling

#define CHECK_PROGRAM_SIZE(incsize) \
	if (maxProgramSize - programSize < incsize) \
		program = (int *)realloc(program, (maxProgramSize *= 2) * sizeof(int))
#define IF_INSTR(instr) if (strcmp(instruction, #instr) == 0)
#define NEXT_COMMAND program[programSize++]

// Inline functions for assembling

inline int registerNumber(string arg)			// Returns number of register arg,
{							// or 0 if arg isn't a register.
	#define _getPos(_STR_, _CHR_) (strchr(_STR_, _CHR_) - _STR_)
	if (!arg)					// ate NULL
		return 0;

	if (	!arg[2] && 				// 2-letter register name (without prefix)
		strchr(REGISTER_POSTFIX, arg[1]) && 
		strchr(REGISTER_LETTER, arg[0]))
		return 	_getPos(REGISTER_LETTER, arg[0]) * NUM_OF_REGS_IN_GROUP +
			strlen(REGISTER_PREFIX) + _getPos(REGISTER_POSTFIX, arg[1]) + 1;

	if (	!arg[3] && 				// 3-letter register name (without postfix)
		arg[2] == REGISTER_POSTFIX[0] &&
		strchr(REGISTER_LETTER, arg[1]) &&
		strchr(REGISTER_PREFIX, arg[0]))
		return 	_getPos(REGISTER_LETTER, arg[1]) * NUM_OF_REGS_IN_GROUP +
			_getPos(REGISTER_PREFIX, arg[0]) + 1;
	#undef _getPos
	return 0;
}


_ERRNO_T assembleString(string sourceStr)
{
	string* saveptr;
	string instruction = strtok_r(sourceStr, DELIM, saveptr);
	char *arg1 = strtok_r(NULL, DELIM, saveptr);
	char *arg2 = strtok_r(NULL, DELIM, saveptr);
	#include "generated/assembler_generated.c"
	return UNKNOWN_COMMAND;
}
