typedef enum _ERRNO { //TODO: check if word _ERRNO could be removed
	SUCCESS,
	INCORRECT_COMMAND_LINE,
	NO_INPUT_FILES,
	CANNOT_OPEN_FILE,
	CANNOT_CLOSE_FILE,
	INPUT_IS_EMPTY,
	CANNOT_ALLOCATE_MEMORY,
	UNKNOWN_COMMAND,
	INVALID_ARGS
} ERRNO_T;

#ifdef INCLUDE_IN_MAIN

const char* errmsg[] = {
	"Assembly successful",
	"Usage: vmm-asm file1 file2 ... -o outputFile"
	"Error: no input files",
	"Error: cannot open file",
	"Error: cannot close file",
	"Error: input file is empty",
	"Error: cannot allocate memory for program",
	"Error: unknown command",
	"Error: invalid combination of command and arguments"
}

inline void parseError(ERRNO_T errno, char *file, size_t line)
{	
	fprintf(stderr, "%s:%d: %s\n", file, line, errmsg[errno]);
	if (errno != SUCCESS)
		finalization(errno);
}

#endif
