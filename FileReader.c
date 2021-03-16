#include "FileReader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "callMemoryAction.h"
#include "MyMemory.h"

#define FILE_BUFFER_SIZE 254

void removeNewLineFromString(char *string);
int areStringEquals(char *string1, char *string2);

int isCommandExists(char *command){
	return areStringEquals(command, "init") ||
		areStringEquals(command, "end") ||
		areStringEquals(command, "alloc") ||
		areStringEquals(command, "desalloc") ||
		areStringEquals(command, "disp");
}

void executeFile(char *path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Cannot open %s", path);
		perror(":");
	}
	else {
		// Read each line of the file
		char buffer[FILE_BUFFER_SIZE + 1];

		char command[FILE_BUFFER_SIZE + 1];
		int value = 0, parametersCount;
		int lineCounter = 1;
		// Read line by line, and execute in the order
		while (fgets(buffer, FILE_BUFFER_SIZE, file) != NULL) {
			removeNewLineFromString(buffer);
			// Try to read a string and a number, but the number is not needed for commands
			// such as "disp" or "end", so the parametersCount checks the number of arguments
			// effectively red.
			parametersCount = sscanf(buffer, "%s %d", command, &value);
			// If parametersCount is 0, we skip this line
			if (parametersCount < 1) {
				printf("Cannot read line %d\n", lineCounter);
			}
			// We have a value if we have read 2 parameters
			else if(!executeCommand(command, parametersCount == 2, value)){
				break;
			}
			lineCounter++;
		}
		//check if memory is free, and do it if not the case
		if (!isMemoryFree()) {
			clearMem();
		}
		fclose(file);
	}
}

void removeNewLineFromString(char *string) {
	string[strcspn(string, "\r\n")] = 0;
}

int executeCommand(char *commandName, int isThereAnyValue, int value) {
	if(!isCommandExists(commandName)){
		printf("The command \"%s\" does not exists\n", commandName);
		return 0;
	}
	if (areStringEquals(commandName, "disp")) {
		displayMem();
	}
	else if (areStringEquals(commandName, "end")) {
		clearMem();
	}
	else {
		if (!isThereAnyValue) {
			printf("The command \"%s\" probably need one integer parameter\n", commandName);
			return 0;
		}
		else {
			if (areStringEquals(commandName, "init")) {
				initMem(value);
			}
			else if (areStringEquals(commandName, "alloc")) {
				allocBlock(value);
			}
			else if (areStringEquals(commandName, "desalloc")) {
				desallocBlock(value);
			}
			else {
				printf("The command \"%s\" does not exists\n", commandName);
				return 0;
			}
		}
	}
	return 1;
}

int areStringEquals(char *string1, char *string2) {
	return strcmp(string1, string2) == 0;
}
