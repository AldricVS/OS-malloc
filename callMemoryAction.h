///@file callMemoryAction.h

#include <stdio.h>
#include <stdlib.h>

/**
 * Initialise the memory, only one memory may be active at any time
 * \param size, the size of the memory
 * \return the size of the memory, or -1 if an error occur
 */
void initMem(int size);
/**
 * Create a block to insert into the memory
 * \param size, the size of the block
 * \return the size of the block, or -1 if an error occur
 *
 */
void allocBlock(int size);
/**
 * Desalloc a block from the list of block in the memory
 * \param nbBlock, the Nth block to free (starting from 0)
 * \return the size of the block, or -1 if an error occur
 */
void desallocBlock(int nbBlock);
/**
 * Display the current state of the Memory
 */
void displayMem();
/**
 * Clear the current memory, allowing another to be created
 */
void clearMem();
