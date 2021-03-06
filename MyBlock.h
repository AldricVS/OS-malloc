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

/**
 * Implementation of the "malloc" function in the context of the project.
 * This will try to find the best valid position in memory (previously initialized)
 * that can holds the new allocated memory. If there is currently not any space where to
 * put the block, but that there is enough space in all memory to hold it, the function 
 * will call "deragMemory".
 * 
 * @param nBytes the number of bytes to allocate
 * @return the pointer of the new "allocated" memory, or NULL if cannot be created (not enough space).   
 * @see defragMemory()
 */
void *myAlloc(int nBytes);

/**
 * Desallocate a previously allocated block in the memory (an array for example).
 * It will remove the block containing the data from the block list.
 * @param contentPtr the pointer of the allocated zone. 
 * 		This is also the "contentPtr" attribute of the "MyBlock" structure.
 * @return the number of bytes freed, or -1 if the operation failed 
 * 		(this can be because the contentPtr cannot be found for example).
 */
int myFree(void *contentPtr);

/**
 * Check if there is enough space between two pointers in order to put a block of memory.
 * It also take account of the size of the block data structure.
 * @param begin the pointer to the begin of the area  
 * @param end the pointer to the end of the area  
 * @param nBytes the number of bytes needed  
 * @return a boolean value showing if there is enough space or not 
 */ 
int isSpaceSufficient(char *begin, char *end, int nBytes);

/**
 * Calculate the space between two pointers, minus the size of the block data structure.
 * @param begin the pointer to the begin of the area
 * @param end the pointer to the end of the area
 * @return the number of bytes between those two pointers (minus the size of the block struct).
 */
int spaceBetweenTwoPtrs(char *begin, char *end);

/**
 * Calculate the space between two blocks, starting from the end of the first block's content.
 * @param firstBlock the pointer to the begin of the area
 * @param secondBlock the pointer to the end of the area
 * @return the number of bytes between those two blocks.
 */
unsigned int spaceBetweenTwoBlocks(MyBlock firstBlock, MyBlock secondBlock);

/**
 * Search in all memory the best place where to put a memory block of nBytes.
 * The best place is the smallest space between all memory blocks that 
 * If needed, this function can call "defragMemory()" 
 * in order to get enough space to put the block.
 * 
 * @param nBytes the size in bytes 
 */
void *searchBestSpace(int nBytes, MyBlock *previousBlock);
void *searchValidSpace(int nBytes, MyBlock *previousBlock);

void displayBlock(MyBlock block);

#endif
