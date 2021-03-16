#ifndef FILE_READER_H
#define FILE_READER_H

/**
 * Read the file line by line and execute all commands from it.
 * Stop immediately if any parsing error is encountered.
 * @param path the path of the file to read.
 */
void executeFile(char *path);

/**
 * Check if the command provided is recognized by the reader
 * @param command the string of the command.
 * @return 1 if the command is within the recognized ones, 0 else.
 */ 
int isCommandExists(char *command);

/**
 * Execute a single command on the memory
 * @param commandName the name of the command. It must exists in the command list
 * @param isThereAnyValue if a value is provided (3rd argument)
 * @param value the value provided, if needed
 * 
 * @return 1 if the command is valid and can be executed, 0 else.
 */ 
int executeCommand(char *commandName, int isThereAnyValue, int value);

#endif
