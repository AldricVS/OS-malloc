#include "MyBlock.h"
#include "MyMemory.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

extern MyMemory memory;

int isSpaceSufficient(char *begin, char *end, int nBytes) {
	unsigned int spaceBetween = end - begin;
	// We need to take account of the size of the block too
	return spaceBetween >= nBytes + sizeof(struct myBlockCel);
}

int spaceBetweenTwoPtrs(char *begin, char *end) {
	return end - begin - sizeof(struct myBlockCel);
}

unsigned int spaceBetweenTwoBlocks(MyBlock firstBlock, MyBlock secondBlock) {
	// Get the end of the first block allocated memory
	char *firstBlockEnd = (char *)firstBlock->contentPtr + firstBlock->contentSize;
	char *seconfBlockBegin = (char *)secondBlock;
	return seconfBlockBegin - firstBlockEnd;
}

void *searchBestSpace(int nBytes, MyBlock *previousBlock) {
	int totalSpaceAvailable = 0;
	int minSpaceSizeAvailable = INT_MAX;
	void *validSpacePtr = NULL;

	// If there is no block now
	if (memory.listBlock == NULL) {
		char *memoryStart = memory.array;
		char *memoryEnd = memoryStart + memory.size;
		if (isSpaceSufficient(memoryStart, memoryEnd, nBytes)) {
			// There is no previous block for this new block
			*previousBlock = NULL;
			return memoryStart;
		}
		else {
			// Not enough space
			return NULL;
		}
	}
	else {
		char *ptrBegin = memory.array;
		char *ptrFirstBlock = (char *)memory.listBlock;
		if (ptrBegin != ptrFirstBlock) {
			totalSpaceAvailable += ptrFirstBlock - ptrBegin;
			// If we can put the new block at the beginning of the memory
			if (isSpaceSufficient(ptrBegin, ptrFirstBlock, nBytes)) {
				// This is our first possible space
				minSpaceSizeAvailable = spaceBetweenTwoPtrs(ptrBegin, ptrFirstBlock);
				previousBlock = NULL;
				validSpacePtr = ptrBegin;
			}
		}
		// Continue the research
		MyBlock block = memory.listBlock;
		MyBlock blockAfter = block->nextBlock;
		char *firstBlockEnd;
		char *secondBlockBegin;
		while (blockAfter != NULL) {
			// If the space between first block end and second block begin is sufficient,
			// compare with the previous min size possible
			firstBlockEnd = (char *)block->contentPtr + block->contentSize;
			secondBlockBegin = (char *)blockAfter;
			totalSpaceAvailable += secondBlockBegin - firstBlockEnd;
			if (firstBlockEnd != secondBlockBegin && isSpaceSufficient(firstBlockEnd, secondBlockBegin, nBytes)) {
				int space = spaceBetweenTwoBlocks(block, blockAfter);
				if (space < minSpaceSizeAvailable) {
					minSpaceSizeAvailable = space;
					*previousBlock = block;
					validSpacePtr = firstBlockEnd;
				}
			}
			block = blockAfter;
			blockAfter = blockAfter->nextBlock;
		}
		// Finally, search between the last block and the end of the memory
		// Here, firstBLock is the lastBlock of the memory
		firstBlockEnd = (char *)block->contentPtr + block->contentSize;
		char *endMemoryPtr = memory.array + memory.size;
		totalSpaceAvailable += endMemoryPtr - firstBlockEnd;
		if (isSpaceSufficient(firstBlockEnd, endMemoryPtr, nBytes)) {
			int space = spaceBetweenTwoPtrs(firstBlockEnd, endMemoryPtr);
			if (space < minSpaceSizeAvailable) {
				minSpaceSizeAvailable = space;
				*previousBlock = block;
				validSpacePtr = firstBlockEnd;
			}
		}
	}
	// Here, the validSpacePtr can be NULL, but we can still have enough space to insert the block
	// if it is the case, we compress all blocks
	if (validSpacePtr == NULL) {
		if (totalSpaceAvailable >= nBytes + sizeof(MyBlock)) {
			//TODO : call the compress function
			return NULL;
		}
		else {
			return NULL;
		}
	}
	return validSpacePtr;
}

void *searchValidSpace(int nBytes, MyBlock *previousBlock) {
	int totalSpaceAvailable = 0;
	int minSpaceSizeAvailable = INT_MAX;
	void *validSpacePtr = NULL;

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
	void *blockPtr = searchBestSpace(nBytes, &previousBlock);
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

void moveBlockInMemory(void* newMemoryPtr, MyBlock movingBlock) {
	int sizeOfBlock = sizeof(MyBlock);
	int totalSizeOfBlock = sizeOfBlock + movingBlock->contentSize;
	for (int i = 0; i < totalSizeOfBlock; i++) {
		memory.array[i] = ((char*)movingBlock)[i];
	}
}

int myFree(void *ptr) {
	// If no memory is allocated yet
	if (memory.listBlock == NULL) {
		return -1;
	}

	int sizeFreed;
	MyBlock currentBlock = memory.listBlock;
	MyBlock previousBlock = NULL;

	//if the first block is the right one, remove it directly
	if (currentBlock->contentPtr == ptr) {
		sizeFreed = currentBlock->contentSize;
		memory.listBlock = currentBlock->nextBlock;
	}
	else {
		// Search the block who have this pointer
		// keep the previous block in order to properly remove it
		while (currentBlock != NULL && currentBlock->contentPtr < ptr) {
			previousBlock = currentBlock;
			currentBlock = currentBlock->nextBlock;
		}
		// If the Block is NULL, we didn't find the pointer associated
		if (currentBlock == NULL || currentBlock->contentPtr != ptr) {
			return -1;
		}

		// Else we free it (remove the corresponding block)
		sizeFreed = currentBlock->contentSize;
		previousBlock->nextBlock = currentBlock->nextBlock;
	}
	currentBlock->contentPtr = NULL;
	return sizeFreed;
}

void displayBlock(MyBlock block) {
	printf("\tBlock address : 0x%p\n", block->contentPtr);
	printf("\tBlock size : %d", block->contentSize);
	printf("\n");
	printf("\t***\n");
}
