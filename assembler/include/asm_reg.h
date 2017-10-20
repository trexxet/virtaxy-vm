// Register types & functions

#pragma once

#include <string.h>
#include "../config.h"


#define IS_REG2(arg) (arg && strlen(arg) == 2 &&          \
		      strchr(REGISTER_POSTFIX, arg[1]) && \
		      strchr(REGISTER_LETTER, arg[0]))

#define IS_REG3(arg) (arg && strlen(arg) == 3 &&         \
		      arg[2] == REGISTER_POSTFIX[0] &&   \
		      strchr(REGISTER_PREFIX, arg[0]) && \
		      strchr(REGISTER_LETTER, arg[1]))

#define IS_REG(arg) (IS_REG2(arg) || IS_REG3(arg))


__attribute__((hot))
int registerNumber(char* arg)  // Returns number of register arg,
{                              // or 0 if arg isn't a register.
	#define _getPos(_STR_, _CHR_) (strchr(_STR_, _CHR_) - _STR_)
	if (!arg)              // ate NULL
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

#define REG_NUM(arg) registerNumber(arg)

