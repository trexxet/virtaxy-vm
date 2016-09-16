typedef enum { 
	SUCCESS,	
	INCORRECT_COMMAND_LINE,		//Usage: vmm-asm file1 file2 ... -o outputFile
	NO_INPUT_FILES,			//Error: no input files
	CANNOT_OPEN_FILE,		//Error: cannot open file
	CANNOT_CLOSE_FILE,		//Error: cannot close file
	INPUT_IS_EMPTY,			//Error: input file is empty
	CANNOT_ALLOCATE_MEMORY,		//Error: cannot allocate memory for program"
	UNKNOWN_COMMAND,		//Error: unknown command"
	INVALID_ARGS			//Error: invalid combination of command and arguments"
} ERRNO_T;
