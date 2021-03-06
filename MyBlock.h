///@file myBlock.h

#ifndef MY_BLOCK_H
#define MY_BLOCK_H

/**
 * A block is an entity that will be in the memory.
 * His purpose is to hold data from allocated blocks and permit
 * to keep trace of them (when allocationg a new memory zone or freeing it).
 * This is a linked list-type structure.
 */
typedef struct myBlockCel {
	/**
	* The size (in bytes) of the "allocated" space with myAlloc
	* (does not count the size of the block itself).
	*/
	unsigned int contentSize;
	/**
	* The pointer of the start of the "allocated" variable.
	*/
	void *contentPtr;
	/**
	* The next block in the list.
	*/
	struct myBlockCel *nextBlock;
}*MyBlock;

void *myAlloc(int nBytes);
int myFree(void *contentPtr);

int isSpaceSufficient(char *begin, char *end, int nBytes);
int spaceBetweenTwoPtrs(char *begin, char *end);
unsigned int spaceBetweenTwoBlocks(MyBlock firstBlock, MyBlock secondBlock);
void *searchBestSpace(int nBytes, MyBlock *previousBlock);
void *searchValidSpace(int nBytes, MyBlock *previousBlock);

void displayBlock(MyBlock block);

#endif
