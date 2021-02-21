#include "MyMemory.h"
#include <stdlib.h>

MyMemory memory;

int initMemory(int nBytes) {
	// Allocate nBytes bytes (char == 1 byte)
	void *ptr = malloc(nBytes * sizeof(char));
	if (ptr == NULL) {
		return -1;
	}
	else {
		// Init memory and return the number of bytes allocated
		memory.size = nBytes;
		memory.isFree = 0;
		memory.array = ptr;
		memory.firstBlock = NULL;
		memory.lastBlock = NULL;
		return nBytes;
	}
}

int freeMemory() {
	// We can't free memory multiple times
	if (memory.isFree) {
		return -1;
	}
	else {
		memory.isFree = 1;
		free(memory.array);
		return memory.size;
	}
}

void insertBlockHead(MyBlock *newBlock) {
	MyBlock firstBlock = memory.firstBlock;
	*newBlock = memory.array;
	if (firstBlock != NULL) {
		(*newBlock)->nextBlock = firstBlock;
	}
	memory.firstBlock = *newBlock;
	if (memory.lastBlock == NULL) {
		memory.lastBlock = *newBlock;
		(*newBlock)->nextBlock = NULL;
	}
}

void insertBlockAfter(MyBlock *newBlock, MyBlock previousBlock) {
	MyBlock afterBlock = previousBlock->nextBlock;
	*newBlock = (char *)previousBlock->contentPtr + previousBlock->contentSize;
	previousBlock->nextBlock = *newBlock;
	(*newBlock)->nextBlock = afterBlock;
	// If the previous block was the last one
	if (afterBlock == NULL) {
		memory.lastBlock = *newBlock;
	}
}

void insertBlockTail(MyBlock *newBlock) {
	MyBlock lastBlock = memory.lastBlock;
	if (lastBlock == NULL) {
		insertBlockHead(newBlock);
	}
	else {
		newBlock = (char *)lastBlock->contentPtr + lastBlock->contentSize;
		lastBlock->nextBlock = *newBlock;
		memory.lastBlock = *newBlock;
		(*newBlock)->nextBlock = NULL;
	}
}
