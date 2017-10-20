// Error codes & explaining strings

#pragma once


typedef enum { 
	SUCCESS = 0,	
	INCORRECT_COMMAND_LINE,
	NO_INPUT_FILES,
	CANNOT_OPEN_FILE,
	CANNOT_CLOSE_FILE,
	INPUT_IS_EMPTY,
	CANNOT_ALLOCATE_MEMORY,
	UNKNOWN_COMMAND,
	INVALID_ARGS
} _ERRNO_T;


#define C_BOLD_RED "\033[1m\033[31m"
#define C_BOLD_BLUE "\033[1m\033[34m"
#define C_RESET "\033[0m"

const static char* errmsg[] = {
	[SUCCESS] = 
		"Assembly successful",
	[INCORRECT_COMMAND_LINE] = 
		C_BOLD_BLUE"Usage:"C_RESET" vmm-asm <source> -o <output>",
	[NO_INPUT_FILES] = 
		C_BOLD_RED"error:"C_RESET" no input files",
	[CANNOT_OPEN_FILE] = 
		C_BOLD_RED"error:"C_RESET" cannot open file",
	[CANNOT_CLOSE_FILE] = 
		C_BOLD_RED"error:"C_RESET" cannot close file",
	[INPUT_IS_EMPTY] = 
		C_BOLD_RED"error:"C_RESET" input file is empty",
	[CANNOT_ALLOCATE_MEMORY] = 
		C_BOLD_RED"error:"C_RESET" cannot allocate memory for program",
	[UNKNOWN_COMMAND] = 
		C_BOLD_RED"error:"C_RESET" unknown command",
	[INVALID_ARGS] = 
		C_BOLD_RED"error:"C_RESET" invalid combination of command and arguments"
};

