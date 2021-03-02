#include "callMemoryAction.h"
#include "MyMemory.h"
#include "MyBlock.h"
#include <stdio.h>

extern MyMemory memory;

void initMem(int size) {
	if (initMemory(size) == -1) {
		puts("Memory initalization failed");
	}
	else {
		printf("Memory initialized with %d bytes\n", size);
	}
}

void allocBlock(int size) {
	if (myAlloc(size) == NULL) {
		puts("Error while doing allocation");
	}
	else {
		printf("New memory of %d bytes allocated\n", size);
	}
}

void desallocBlock(int nbBlock) {
	MyBlock wantedBlock = getNBlockInList(nbBlock);
	if (wantedBlock == NULL) {
		puts("Not enough blocks in the list");
	}
	else {
		if (myFree(wantedBlock->contentPtr) == -1) {
			printf("Cannot free the block n %d\n", nbBlock);
		}
		else {
			printf("Free the block n %d:\n", nbBlock);
		}
	}
	
}

void displayMem() {
    displayMemory();
}

void clearMem() {
	if (freeMemory() == -1) {
		puts("Memory already freed");
	}
	else {
		puts("Memory now free");
	}
}
