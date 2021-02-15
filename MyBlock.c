#include "MyBlock.h"
#include "MyMemory.h"
#include <stdlib.h>

extern MyMemory memory;

void *myAlloc(int nBytes) {
	/*
	 * For now, this will just create a new block at the end of the list,
	 * no matter the fragmentation
	 */

	// Search the last block, if NULL, there is nothing in the memory
	MyBlock lastBlock = memory.lastBlock;
	MyBlock block;
	if (lastBlock == NULL) {
		//set it to the very beginning of the memory
		block = (void*)memory.array;
		memory.firstBlock = block;
		memory.lastBlock = block;
	}
	else {
		char *p = (char *)memory.lastBlock->contentPtr + memory.lastBlock->contentSize;
		p -= 16; //PAS NORMAL
		block = (MyBlock)p;
		//don't forget the size of a block
		block++;
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
