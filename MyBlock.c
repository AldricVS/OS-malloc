#include "MyBlock.h"
#include "MyMemory.h"
#include <stdlib.h>

extern MyMemory memory;

int isSpaceSufficient(char *begin, char *end, int nBytes) {
	unsigned int spaceBetween = end - begin;
	// We need to take account of the size of the block too
	return spaceBetween >= nBytes + sizeof(struct myBlockCel);
}

unsigned int spaceBetweenTwoBlocks(MyBlock firstBlock, MyBlock secondBlock) {
	// Get the end of the first block allocated memory
	char *firstBlockEnd = (char *)firstBlock->contentPtr + firstBlock->contentSize;
	char *seconfBlockBegin = (char *)secondBlock;
	return seconfBlockBegin - firstBlockEnd;
}

void *searchValidSpace(int nBytes, MyBlock *previousBlock) {
	// If there is no block now
	if (memory.listBlock == NULL) {
		char *memoryStart = memory.array;
		char *memoryEnd = memoryStart + memory.size;
		if (isSpaceSufficient(memoryStart, memoryEnd, nBytes)) {
			// There is no previous block for this new block
			*previousBlock = NULL;
			return memoryStart;
		}
	}
	else {
		// If there is one, search the space between the begin of the space and the first block
		char *ptrBegin = memory.array;
		char *ptrFirstBlock = (char *)memory.listBlock;
		if (ptrBegin != ptrFirstBlock) {
			// If we can put the new block at the beginning of the memory
			if (isSpaceSufficient(ptrBegin, ptrFirstBlock, nBytes)) {
				// There is no previous block for this new block
				*previousBlock = NULL;
				return ptrBegin;
			}
		}
		// Else, we have to go through each of the blocks and find a sufficient space
		MyBlock firstBlock = memory.listBlock;
		MyBlock nextBlock = firstBlock->nextBlock;
		char *firstBlockEnd;
		char *secondBlockBegin;
		while (nextBlock != NULL) {
			// If the space between first block end and second block begin is sufficient,
			// return the pointer to the and of the first block
			firstBlockEnd = (char *)firstBlock->contentPtr + firstBlock->contentSize;
			secondBlockBegin = (char *)nextBlock;
			if (firstBlockEnd != secondBlockBegin && isSpaceSufficient(firstBlockEnd, secondBlockBegin, nBytes)) {
				// The previous block if the firstBlock
				*previousBlock = firstBlock;
				return firstBlockEnd;
			}
			firstBlock = nextBlock;
			nextBlock = nextBlock->nextBlock;
		}
		// Finally, search between the last block and the end of the memory
		// Here, firstBLock is the lastBlock of the memory
		firstBlockEnd = (char *)firstBlock->contentPtr + firstBlock->contentSize;
		char *endMemoryPtr = memory.array + memory.size;
		if (isSpaceSufficient(firstBlockEnd, endMemoryPtr, nBytes)) {
			// The previous block if the firstBlock
			*previousBlock = firstBlock;
			return firstBlockEnd;
		}
	}
	//we didn't find any sufficient space in the memory
	return NULL;
}

void *myAlloc(int nBytes) {
	if (memory.isFree == 1) {
		printf("Error while allocating Block memory :\n\tMemory is not initialized");
		return NULL;
	}

	MyBlock previousBlock = NULL;
	void *blockPtr = searchValidSpace(nBytes, &previousBlock);
	if (blockPtr == NULL) {
		return NULL;
	}
	else {
		//create a new block and add it in the memory at the right position
		MyBlock block = NULL;
		// If previsousBlock is NULL, this block is the new firstBlock of the memory
		if (previousBlock == NULL) {
			insertBlockHead(&block);
		}
		else {
			//On devrait rajouter notre block après un autre qu'une fois qu'on ait atteint la fin de notre mémoire ?
			//insertBlockTail(&block);
			insertBlockAfter(&block, previousBlock);
		}
		if (block == NULL) {
			printf("Error while allocating Block memory :\n\tBlock value is NULL\n");
			return NULL;
		}
		block->contentSize = nBytes;
		// Let the space for the struct (pointer arithmetic)
		block->contentPtr = block + 1;
		return block->contentPtr;
	}
}

int myFree(void *ptr) {
	// If no memory is allocated yet
	if (memory.listBlock == NULL) {
		return -1;
	}

	int sizeFreed;
	//if the first block is the right one, remove it directly
	if (memory.listBlock->contentPtr == ptr) {
		sizeFreed = memory.listBlock->contentSize;
		memory.listBlock = memory.listBlock->nextBlock;
	}
	else {
		// Search the block who have this pointer
		// keep the previous block in order to properly remove it
		MyBlock currentBlock = memory.listBlock;
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
