#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "errors.h"
#include "config.h"

#include "generated/opcodes.h"


uint8_t* program = NULL;
size_t maxProgramSize = INIT_PROGRAM_SIZE;
size_t programSize = 0;


_ERRNO_T asmInit()
{
	return (program = calloc(INIT_PROGRAM_SIZE, 1)) ? SUCCESS : CANNOT_ALLOCATE_MEMORY;
}


// Macros for assembling

#define CHECK_PROGRAM_SIZE(incsize)                                  \
	if (maxProgramSize - programSize < incsize)                  \
		program = (uint8_t *) realloc(program,               \
		           (maxProgramSize += maxProgramSize * 2) * sizeof(uint8_t))

#define IF_INSTR(instr) if (strcmp(instruction, #instr) == 0)

#define NEXT_COMMAND program[programSize++]

#define IS_REG2(arg) (arg && strlen(arg) == 2 &&          \
	              strchr(REGISTER_POSTFIX, arg[1]) && \
	              strchr(REGISTER_LETTER, arg[0]))

#define IS_REG3(arg) (arg && strlen(arg) == 3 &&         \
	              arg[2] == REGISTER_POSTFIX[0] &&   \
	              strchr(REGISTER_PREFIX, arg[0]) && \
	              strchr(REGISTER_LETTER, arg[1]))

#define IS_REG(arg) (IS_REG2(arg) || IS_REG3(arg))

#define REG_NUM(arg) registerNumber(arg)

#define IS_NUM(arg) (arg && strspn(arg, "012456789") == strlen(arg))


// Argument types

typedef enum {
	NONE = 0,
	NUM,
	REG
} argType;

typedef struct {
	char *str;
	argType type;
} arg_t;


// Functions for assembling

__attribute__((hot))
int registerNumber(char* arg)  // Returns number of register arg,
{                              // or 0 if arg isn't a register.
	#define _getPos(_STR_, _CHR_) (strchr(_STR_, _CHR_) - _STR_)
	if (!arg)          // ate NULL
		return 0;

	if (IS_REG2(arg))      // 2-letter register name (without prefix)
		return 	_getPos(REGISTER_LETTER, arg[0]) * NUM_OF_REGS_IN_GROUP +
		        strlen(REGISTER_PREFIX) + _getPos(REGISTER_POSTFIX, arg[1]) + 1;

	if (IS_REG3(arg))      // 3-letter register name (without postfix)
	    return _getPos(REGISTER_LETTER, arg[1]) * NUM_OF_REGS_IN_GROUP +
		   _getPos(REGISTER_PREFIX, arg[0]) + 1;

	#undef _getPos
	return 0;
}


__attribute__((hot))
_ERRNO_T assembleString(char *sourceStr)
{
	char **saveptr;
	char *instruction = strtok_r(sourceStr, DELIM, saveptr);
	
	arg_t arg1, arg2;
	arg1.str = strtok_r(NULL, DELIM, saveptr);
	arg2.str = strtok_r(NULL, DELIM, saveptr);
	arg1.type = IS_NUM(arg1.str) + IS_REG(arg1.str) * 2;
	arg2.type = IS_NUM(arg2.str) + IS_REG(arg2.str) * 2;
	if ((arg1.str && arg1.type == NONE) ||
	    (arg2.str && arg2.type == NONE))
		return INVALID_ARGS;
	#include "generated/asm_generated.c"
	return UNKNOWN_COMMAND;
}

