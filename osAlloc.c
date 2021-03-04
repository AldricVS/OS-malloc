#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MyMemory.h"
#include "MyBlock.h"
#include "InteractionMenu.h"
#include "FileReader.h"
#include "CliReader.h"
#include "util.h"

extern MyMemory memory;

struct V {
	int a;
	char b;
};

int test();

int main(int argc, char** argv) {
	if (argc > 1) {
		char* param = argv[1];
		if (strcmp(param,"-i") == 0) {
			if (argc == 2) {
				printf("Lauching interactive version...\n");
				interactionLoop();
			}
			else {
				printf("Too many arguments for the interactive version : require only 1 argument\n");
			}
		}
		else if (strcmp(param,"-f") == 0) {
			if (argc == 3) {
				printf("Lauching file version...\n");
				executeFile(argv[2]);
			}
			else {
				printf("Incorrect number of arguments to start reading the file\n");
				printf("Expected : -f [fileName]\n");
			}
		}
		else {
			printf("Lauching command line version...\n");
			//example of working program call : osAlloc -init 20000 -alloc 500 -alloc 10 -disp -desalloc 0 -disp -end
			executeCliArgs(argc, argv);
		}
	}
	else {
		printf("Lauching test program...\n");
		return test();
	}
	return 0;
}

int test() {
	printf("======== Start of the test ========\n");
	int memorySize = 2000;
	if (initMemory(memorySize) == -1) {
		printf("Cannot initialize memory of %d bytes\n", memorySize);
		return 1;
	}
	printf("Memory Initialize\n");

	//no errors in myAlloc for now
	int *a = myAlloc(12 * sizeof(int));
	for (int i = 0; i < 12; i++) {
		a[i] = i;
	}
	printf("Block a Initialized\n");

	int *b = myAlloc(15 * sizeof(int));
	for (int i = 0; i < 15; i++) {
		b[i] = i * 3;
	}
	printf("Block b Initialized\n");

	int *c = myAlloc(9 * sizeof(int));
	for (int i = 0; i < 9; i++) {
		c[i] = i - 2;
	}
	printf("Block c Initialized\n");

	struct V *v = myAlloc(10 * sizeof(struct V));
	for (int i = 0; i < 9; i++) {
		v[i].a = 127 + i;
		v[i].b = 'a' + i;
	}
	puts("Struct V Initialized\n");

	puts("Display all arrays content :");
	displayArray(10, a);
	displayArray(memory.listBlock->contentSize / sizeof(int), memory.listBlock->contentPtr);
	displayArray(15, b);
	displayArray(9, c);
	printf("Fin affichage Tab\n");

	printf("\nDisplay memory with arrays a, b, c & v\n");
	displayMemory();

	printf("\nFree a array\n");
	myFree(a);
	printf("a array is now free\n");

	printf("\nMemory without array a :\n");
	displayMemory();

	int *d = myAlloc(5 * sizeof(int));
	for (int i = 0; i < 5; i++) {
		d[i] = 20 * i;
	}
	printf("Block d Initialized\n");

	displayArray(5, a);

	int res = myFree(c);
	if (res == -1) {
		perror("Error while freeing\n");
	}
	else {
		printf("%d\n", res);
		printf("%d\n", myFree(v));
	}

	printf("\nDisplay memory with arrays in order : d (size : 5 bytes), b (size : 15 bytes)\n");
	displayMemory();

	printf("Insert memory e, of size 4 between d and b\n");
	int *e = myAlloc(sizeof(int));
	*e = 2;
	displayMemory();

	freeMemory();
	printf("======== End of the test ========\n");
	return 0;
}
