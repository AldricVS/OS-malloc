#include "CliReader.h"
#include "callMemoryAction.h"
#include "util.h"
#include <stdio.h>

int executeArgument(int *argCounter, int argc, char **argv) {
	// Check if this arg index really exists
	if (*argCounter >= argc) {
		return 0;
	}
	// Retrieve the arg and do something depending on it
	char *arg = argv[*argCounter];
	// disp & end does not need a second argument
	if (areStringsEquals(arg, "-disp")) {

	}
	else if (areStringsEquals(arg, "-end")) {

	}
	else {

	}
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
}
