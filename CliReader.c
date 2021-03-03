#include "CliReader.h"
#include "callMemoryAction.h"
#include "util.h"
#include "MyMemory.h"
#include <stdio.h>
#include <string.h>

int executeArgument(int *argCounter, int argc, char **argv) {
	// Check if this arg index really exists
	if (*argCounter >= argc) {
		printf("Cannot read any argument\n");
		return 0;
	}
	// Retrieve the arg and do something depending on it
	char *arg = argv[*argCounter];
	// disp & end does not need a second argument
	if (areStringsEquals(arg, "-disp")) {
		displayMem();
	}
	else if (areStringsEquals(arg, "-end")) {
		clearMem();
	}
	else {
		// We need a second argument after this one
		(*argCounter)++;
		if (*argCounter >= argc) {
			printf("No value after the option %s\n", arg);
			return 0;
		}
		else {
			// Check if next parameter is a valid number
			char *secondArg = argv[*argCounter];
			char *endPtr;
			int num = (int)strtol(secondArg, &endPtr, 10);
			if (*endPtr != '\0') {
				printf("\"%s\" is not a valid number. Either you wrote an option that needs an number without the number, or the number is not valid\n", secondArg);
				return 0;
			}

			// Check the remaining possible arguments
			if (areStringsEquals(arg, "-init")) {
				initMem(num);
			}
			else if (areStringsEquals(arg, "-alloc")) {
				allocBlock(num);
			}else if (areStringsEquals(arg, "-desalloc")) {
				desallocBlock(num);
			}
			else {
				printf("Command not recognized\n");
				return 0;
			}
		}
	}
	//increase the counter for the next iteration
	(*argCounter)++;
	return 1;
}

void executeCliArgs(int argc, char **argv) {
	//we start from the argument 1 (0 is the name of the program)
	int argCounter = 1;
	char isThereError = 0;
	while (argCounter < argc && !isThereError) {
		if (!executeArgument(&argCounter, argc, argv)) {
			printf("error while reading %dth argument, end of the program\n", argCounter);
			isThereError = 1;
		}
	}
	// If memory is not free here, do it
	if (!isMemoryFree()) {
		clearMem();
	}
}
