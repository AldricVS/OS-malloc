/**
* @File CliReader.h 
*/

#ifndef CLI_READER_H
#define CLI_READER_H

/**
* Read all commands in order from the aguments given by the user.
* @param argc the number of arguments
* @param argv the array of arguments (array of strings)
*/
void executeCliArgs(int argc, char **argv);

/**
* Execute one argument from the list.
* @param argCounter reference to the index of the argument to read (so that it can be changed by the function if it needs to read more than 1 argument)
* @param argc the number of arguments
* @param argv the array of arguments
* @return 1 if no read issues occurs, 0 if there is any error
*/
int executeArgument(int *argCounter, int argc, char **argv);

#endif // !CLI_READER_H

