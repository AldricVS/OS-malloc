#include "MyMemory.h"
#include <stdlib.h>

MyMemory memory;

int initMemory(int nBytes) {
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

void clearListBlock() {
	MyBlock currentBlock = memory.listBlock;
	while (currentBlock != NULL) {
		MyBlock blockToFree = currentBlock;
		currentBlock = currentBlock->nextBlock;
		freeBlock(blockToFree);
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
	if (firstBlock != NULL) {
		(*newBlock)->nextBlock = firstBlock;
	}
	(*newBlock) = memory.array;
	memory.listBlock = *newBlock;
}

void insertBlockAfter(MyBlock *newBlock, MyBlock previousBlock) {
	MyBlock afterBlock = previousBlock->nextBlock;
	(*newBlock) = (char *)previousBlock->contentPtr + previousBlock->contentSize;
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
		(*newBlock) = (char *)lastBlock->contentPtr + lastBlock->contentSize;
		lastBlock->nextBlock = *newBlock;
		(*newBlock)->nextBlock = NULL;
	}
}

void freeBlock(MyBlock block) {
	block->contentPtr = NULL;
	free(block);
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
