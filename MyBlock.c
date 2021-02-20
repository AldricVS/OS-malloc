#include "MyBlock.h"
#include "MyMemory.h"
#include <stdlib.h>

extern MyMemory memory;

int isSpaceSufficient(char *begin, char *end, int nBytes) {
	unsigned int spaceBetween = end - begin;
	// We need to take account of the size of the block too
	return spaceBetween >= nBytes + sizeof(struct myBlockCel);
}

void *searchValidSpace(int nBytes) {
	// TODO : finir la fonction searchValidSpace (oui ça serait cool)

	// If there is one, search the space between the begin of the space and the first block
	char *ptrBegin = memory.array;
	char *ptrFirstBlock = memory.firstBlock;
	if (ptrBegin != ptrFirstBlock) {
		// If we can put the new block at the beginning of the memory
		if(isSpaceSufficient(ptrBegin, ptrFirstBlock, nBytes)){
			return ptrBegin;
		}
	}
	// Else, we have to go through each of the blocks and find a sufficient space
	MyBlock firstBlock = memory.firstBlock;
	MyBlock nextBlock = firstBlock->nextBlock;
	// Finally, search between the last block and the end of the memory
}

void *myAlloc(int nBytes) {
	MyBlock block;
	// If no block is present, add it at the beginning

	/*if (memory.lastBlock == NULL) {
		if (isSpaceSufficient(memory.array, memory.array + memory.size, nBytes)) {
			block = (void *)memory.array;
			memory.firstBlock = block;
			memory.lastBlock = block;
		}
		else {
			// No enough space to store it
			return -1;
		}
	}*/

	/*
	 * For now, this will just create a new block at the end of the list,
	 * no matter the fragmentation
	 */
	//searchValidSpace(nBytes);

	// Search the last block, if NULL, there is nothing in the memory
	MyBlock lastBlock = memory.lastBlock;
	if (lastBlock == NULL) {
		//set it to the very beginning of the memory
		block = (void*)memory.array;
		memory.firstBlock = block;
		memory.lastBlock = block;
	}
	else {
		char *p = (char *)memory.lastBlock->contentPtr + memory.lastBlock->contentSize;
		block = (MyBlock)p;
		memory.lastBlock->nextBlock = block;
		memory.lastBlock = block;
	}
	block->contentSize = nBytes;
	// Let the space for the struct (pointer arithmetic)
	block->contentPtr = block + 1;
	// This is the last block of the list
	// TODO : change it when the function will be less one-way
	block->nextBlock = NULL;
	
	// TODO : check if there is enough space to alloc
	return block->contentPtr;
}

int myFree(void *ptr) {
	int sizeFreed;
	// If memory is not allocated anymore 
	if (memory.firstBlock == NULL) {
		return -1;
	}

	//if the first block is the right one, remove it directly
	if (memory.firstBlock->contentPtr == ptr) {
		sizeFreed = memory.firstBlock->contentSize;
		memory.firstBlock = memory.firstBlock->nextBlock;
	}
	else {
		// Search the block who have this pointer
		// keep the previous block in order to properly remove it
		MyBlock currentBlock = memory.firstBlock;
		MyBlock nextBlock = currentBlock->nextBlock;
		while (nextBlock != NULL && nextBlock->contentPtr < ptr) {
			currentBlock = nextBlock;
			nextBlock = currentBlock->nextBlock;
		}
		// If currentBlock-> is still NULL, we didn't find the pointer associated
		if (nextBlock == NULL || nextBlock->contentPtr != ptr) {
			return -1;
		}

		// Else we free it (remove the corresponding block)
		sizeFreed = nextBlock->contentSize;
		currentBlock->nextBlock = nextBlock->nextBlock;
	}
	return sizeFreed;
}
