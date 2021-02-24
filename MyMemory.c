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
	MyBlock previousBlock = memory.listBlock;
	int sizeFreed;

	if (previousBlock == block) {
		//memory.listBlock = block->nextBlock;
		sizeFreed = myFree(block->contentPtr);
		if (sizeFreed != block->contentSize) {
			perror("Error when freeing Block :\n\tReturning memory value do not match block size\n");
			exit(-1);
		}
	}
	else {
		while ((previousBlock->nextBlock != NULL) && (previousBlock->nextBlock != block)) {
			previousBlock = (*previousBlock).nextBlock;
		}
		if (previousBlock->nextBlock == block) {
			sizeFreed = myFree(block->contentPtr);
			//previousBlock->nextBlock = block->nextBlock;
			if (sizeFreed != block->contentSize) {
				perror("Error when freeing Block :\n\tReturning memory value do not match block size\n");
				exit(-1);
			}
		}
	}
	//return sizeFreed;
}
