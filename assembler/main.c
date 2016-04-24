#include "main.h"

void main(int argc, char *argv[])
{
	ERRNO_T errno = asmInit(INIT_PROGRAM_SIZE);
	if (argc == 1)
		parseError(NO_INPUT_FILES, "NULL", 0);
	for (uint16_t fileCounter = 1; fileCounter < argc; fileCounter++)
	{
		char *fileName = argv[fileCounter];
		FILE *sourceFile = fopen(fileName, "r");
		if (!sourceFile)
			parseError(CANNOT_OPEN_FILE, fileName, 0);
		if (feof(sourceFile))
			parseError(INPUT_IS_EMPTY, fileName, 0);
		char sourceString[SOURCE_STRING_LENGTH];
		size_t lineCounter = 0;
		while (fgets(sourceString, SOURCE_STRING_LENGTH, sourceFile) && (errno == 0))
		{
			errno = assembleString(sourceString);
			lineCounter++;
		}
		fclose(sourceFile);
		parseError(errno, fileName, lineCounter);
	}
	finalization(SUCCESS);
}

void finalization(ERRNO_T errno)
{
	exit(errno);
}
