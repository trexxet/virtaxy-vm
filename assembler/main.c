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
		dynAllocMem.openedFileHandle = fopen(fileName, "r");
		if (!dynAllocMem.openedFileHandle)
			parseError(CANNOT_OPEN_FILE, fileName, 0);
		if (feof(dynAllocMem.openedFileHandle))
			parseError(INPUT_IS_EMPTY, fileName, 0);
		char sourceString[SOURCE_STRING_LENGTH];
		size_t lineCounter = 0;
		while (fgets(sourceString, SOURCE_STRING_LENGTH, dynAllocMem.openedFileHandle) && (errno == 0))
		{
			errno = assembleString(sourceString);
			lineCounter++;
		}
		fclose(dynAllocMem.openedFileHandle);
		dynAllocMem.openedFileHandle = NULL;
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
	dynAllocMem.fileListNames = inputFileList -> name = (char**) calloc(inputFileList -> num, sizeof(char*));
	for (int i = 0; i < inputFileList -> num; i++)
		inputFileList -> name[i] = argv[i + optind];
}
	
void finalization(ERRNO_T errno)
{
#define FREE(_FUNC_, _POINTER_)				 \
	if (dynAllocMem._POINTER_) {		 \
		_FUNC_(dynAllocMem._POINTER_);	 \
		dynAllocMem._POINTER_ = NULL;	 \
	}
	FREE(fclose, openedFileHandle);
	FREE(free, fileListNames);
#undef FREE
	exit(errno);
}
