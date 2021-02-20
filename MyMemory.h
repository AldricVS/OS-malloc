#ifndef MY_MEMORY_H
#define MY_MEMORY_H
#include "MyBlock.h"

/**
* MyMemory contains an array is where myAlloc and myFree will "work"
*/
typedef struct mymemory{
	unsigned int size;
	int isFree;
	char *array;
	struct myBlockCel *firstBlock;
	struct myBlockCel *lastBlock;
}MyMemory;

int initMemory(int nBytes);
int freeMemory();

void insertBlockHead(MyBlock newBlock);
void insertBlockAfter(MyBlock newBlock, MyBlock previousBlock);
void insertBlockTail(MyBlock newBlock);

#endif // MY_MEMORY_H