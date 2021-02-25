#ifndef MY_BLOCK_H
#define MY_BLOCK_H

/**
 * A block is an entity that will be in the memory.
 * His purpose is to hold data from allocated blocks and permit
 * to keep trace of them (when allocationg a new memory zone or freeing it)
 */
typedef struct myBlockCel {
	unsigned int contentSize;
	void *contentPtr;
	struct myBlockCel *nextBlock;
}*MyBlock;

void *myAlloc(int nBytes);
int myFree(void *contentPtr);

int isSpaceSufficient(char *begin, char *end, int nBytes);
unsigned int spaceBetweenTwoBlocks(MyBlock firstBlock, MyBlock secondBlock);
void *searchValidSpace(int nBytes, MyBlock *previousBlock);

void displayBlock(MyBlock block);

#endif
