#include "main.h"

void main(int argc, char *argv[])
{
	ERRNO_T errno = asmInit(INIT_PROGRAM_SIZE);
	inputFileList_t inputFileList = {NULL, 0};
	char *outputFilename = DEFAULT_OUTPUT_FILENAME;
	parseCommandLineArguments(argc, argv, &inputFileList, outputFilename);

	for (uint16_t fileCounter = 0; fileCounter < inputFileList.num; fileCounter++)
	{
		char *fileName = inputFileList.name[fileCounter];
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

void parseCommandLineArguments(int argc, char *argv[], inputFileList_t *inputFileList, char *outputFilename);
{
	int opt;
	opterr = 0;
	while ((opt = getopt(argc, argv, COMMAND_LINE_OPTIONS)) != -1)
		switch (opt)
		{
			case 'o':
				outputFilename = optarg;
				break;
			case '?':
				parseError(INCORRECT_COMMAND_LINE);
				break;
		}
	inputFileList -> num = argc - optind;
	if (inputFileList -> num == 0)
		parseError(NO_INPUT_FILES, NULL, 0);
	inputFileList -> name = (char**) calloc(inputFileList -> num, sizeof(char*));
	for (int i = 0; i < inputFileList -> num; i++)
		inputFileList -> name[i] = argv[i + optind];
}
	
void finalization(ERRNO_T errno)
{
	exit(errno);
}
