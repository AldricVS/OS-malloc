///@file myMemory.h

#ifndef MY_MEMORY_H
#define MY_MEMORY_H
#include "MyBlock.h"

/**
* MyMemory contains an array is where myAlloc and myFree will "work".
* It has to be initialized before with the function "initMemory" in order to work.
* Also, before exiting the program, it is preferable to use the function "freeMemory", in order to free all data.
* @see initMemory()
* @see freeMemory()
*/
typedef struct mymemory {
	/**
	* The total size (in bytes) of the memory.
	*/
	unsigned int size;
	/**
	* isFree permits to know if the memory was correctly initialized.
	* Before using "initMemory", the value of this variable is unknown.
	*/
	int isFree;
	/**
	* An array of bytes, on wich all blocks created and all arrays, pointers, etc. will be stored.
	*/
	char *array;
	/**
	* listBlock represent the address of the first block of the memory array.
	* This is not certain that this block is on the very begining of the memory (mostly if the first block is removed and no realloc was done).
	*/
	struct myBlockCel *listBlock;
}MyMemory;


//======= MAIN MEMORY FUNCTIONS =======//

/**
* Initialize the memory : it will call the real "malloc" function in order to allocate the array of bytes.
* @param nBytes The number of bytes that the memory will be able to handle.
* @return the number of bytes allocated, or -1 if the "malloc" function failed.
*/
int initMemory(int nBytes);

/**
* Display the memory infos on the standard outpout.
*/
void displayMemory();

/**
* Check if the memory is freed or not
*/
int isMemoryFree();

/**
* Removes all blocks previously added in the memory. So, clear the memory.
*/
void clearListBlock();

/**
* Desallocate the array of bytes and set the "isFree" attribute if the memory to '0'.
* This function must be called before exiting the program.
* @return the number of bytes freed, or -1 if the memory was already free.
*/
int freeMemory();


//======= HELPERS FUNCTIONS ========//

/**
* Insert a block at the very beginning of the memory.
* This only must be done if there is enough space between
* the start of the memory array and the current first block.
* @param newBlock the block to add
*/
void insertBlockHead(MyBlock *newBlock);

/**
* Insert a block right after an other one.
* This only must be done if there is enough space between
* the block and his current nextBlock.
* @param newBlock the block to add
* @param previousBlock after which block add this new block
*/
void insertBlockAfter(MyBlock *newBlock, MyBlock previousBlock);

/**
* Insert a block after the last block of the memory.
* This only must be done if there is enough space between
* the end of the memory array and the current last block.
* @param newBlock the block to add
*/
void insertBlockTail(MyBlock *newBlock);

/**
* Free a specified block from the memory.
* It will assume that the block is in the memory's block list
*/
void freeBlock(MyBlock block);

/**
* Try to get the nth block of the list of blocks (with n starting from 0).
* @param nbBlock the position of the block in the list
* @return the block at the given position, or NULL if the number of blocks in the list is too small
*/
MyBlock getNBlockInList(int nbBlock);

#endif // MY_MEMORY_H
