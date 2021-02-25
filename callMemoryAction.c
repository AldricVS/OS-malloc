#include "callMemoryAction.h"

extern MyMemory memory;

void initMem(int taille) {
	initMemory(taille);
}

void allocBlock(int taille) {
	myAlloc(taille);
}

void desallocBlock(int nbBlock) {
	MyBlock wantedBlock = getNBlockInList(nbBlock);
	myFree(wantedBlock->contentPtr);
}

void displayMem() {
    displayMemory();
}

void clearMem() {
	freeMemory();
}
