#include "MyMemory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MyMemory memory;

int initMemory(int nBytes) {
	///check if memory isn't already in use
	if ((memory.array != NULL) && (memory.isFree != 1)) {
		printf("Memory is already created\n");
		printf("Size of current memory: %d\n", memory.size);
		return -1;
	}
	///check if the asked amount of bytes at least enough to store an int
	if (nBytes < sizeof(struct myBlockCel) + 4) {
		printf("Memory size is too small\n");
		return -1;
	}
	// Allocate nBytes bytes (char == 1 byte)
	void *ptr = malloc(nBytes * sizeof(char));
	if (ptr == NULL) {
		return -1;
	}

	// Init memory and return the number of bytes allocated
	memory.size = nBytes;
	memory.isFree = 0;
	memory.array = ptr;
	memory.listBlock = NULL;
	return nBytes;
}

void displayMemory() {
	printf("******\n");
	printf("Memory state :\n");
	printf("\tMemory size : %d\n", memory.size);
	printf("\tIs memory free : %s\n", memory.isFree?"true":"false");
	printf("\n");
	printf("List of Block contained :\n");

	MyBlock currentBlock = memory.listBlock;
	while (currentBlock != NULL) {
		displayBlock(currentBlock);
		currentBlock = currentBlock->nextBlock;
	}
	printf("******\n");
}

int isMemoryFree() {
	return memory.isFree;
}

void clearListBlock() {
	MyBlock currentBlock = memory.listBlock;
	while (currentBlock != NULL) {
		MyBlock blockToFree = currentBlock;
		currentBlock = currentBlock->nextBlock;
		freeBlock(blockToFree);
	}
}

void moveBlock(MyBlock *blockToMove, char *destination) {
	int spaceToCopy = sizeof(MyBlock) + (*blockToMove)->contentSize;
	char *data = (char *)(*blockToMove);
	for (int i = 0; i < spaceToCopy; i++) {
		destination[i] = data[i];
	}
	*blockToMove = destination;
	// Move also the content pointer
	(*blockToMove)->contentPtr = destination + sizeof(MyBlock);
}

void defragMemory() {
	if (isMemoryFree()) {
		printf("Impossible to defragment memory :\n\tMemory is free\n");
		return;
	}
	else if (memory.listBlock == NULL) {
		printf("Cannot defrag memory : No memory block is curently allocated\n");
		return;
	}
	void *endBlockPtr = NULL;
	// Check first block that is right to the beginning
	MyBlock block = memory.listBlock;
	if ((char*)block > memory.array) {
		moveBlock(&block, memory.array);
	}

	// Then, check all blocks in the list
	MyBlock previousBlock = block;
	block = block->nextBlock;
	while (block != NULL) {
		char *endPreviousBlockPtr = (char *)previousBlock->contentPtr + previousBlock->contentSize;
		int index = endPreviousBlockPtr - memory.array;
		char *blockBeginPtr = (char *)block;
		index = blockBeginPtr - memory.array;
		if (endPreviousBlockPtr != blockBeginPtr) {
			moveBlock(&block, endPreviousBlockPtr);
			previousBlock->nextBlock = (MyBlock)endPreviousBlockPtr;
			block = (MyBlock)endPreviousBlockPtr;
		}
		previousBlock = block;
		block = block->nextBlock;
	}
}

int freeMemory() {
	// We can't free memory multiple times
	if (memory.isFree) {
		return -1;
	}
	else {
		memory.isFree = 1;
		clearListBlock();
		free(memory.array);
		return memory.size;
	}
}

/**
Utiliser cette méthode peut faire que 2 block se partage le même espace mémoire ?
A tester ...
*/
void insertBlockHead(MyBlock *newBlock) {
	MyBlock firstBlock = memory.listBlock;
	(*newBlock) = (void*)memory.array;
	if (firstBlock != NULL) {
		(*newBlock)->nextBlock = firstBlock;
	}
	else {
		(*newBlock)->nextBlock = NULL;
	}
	memory.listBlock = *newBlock;
}

void insertBlockAfter(MyBlock *newBlock, MyBlock previousBlock) {
	MyBlock afterBlock = previousBlock->nextBlock;
	(*newBlock) = (void*)((char *)previousBlock->contentPtr + previousBlock->contentSize);
	previousBlock->nextBlock = *newBlock;
	(*newBlock)->nextBlock = afterBlock;
}

void insertBlockTail(MyBlock *newBlock) {
	MyBlock lastBlock = memory.listBlock;
	if (lastBlock == NULL) {
		insertBlockHead(newBlock);
	}
	else {
		MyBlock nextBlock = lastBlock->nextBlock;
		while (nextBlock != NULL) {
			lastBlock = nextBlock;
			nextBlock = nextBlock->nextBlock;
		}
		(*newBlock) = (void*)((char *)lastBlock->contentPtr + lastBlock->contentSize);
		lastBlock->nextBlock = *newBlock;
		(*newBlock)->nextBlock = NULL;
	}
}

void freeBlock(MyBlock block) {
	block->contentPtr = NULL;
	//free(block);
	block = NULL;
}

MyBlock getNBlockInList(int nbBlock) {
	MyBlock myBlock = memory.listBlock;
	while (nbBlock > 0) {
		if (myBlock != NULL) {
			myBlock = myBlock->nextBlock;
		}
		nbBlock--;
	}
	return myBlock;
}
