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
	struct myBlockCel *listBlock;
}MyMemory;

int initMemory(int nBytes);
void displayMemory();
void clearListBlock();
int freeMemory();

void insertBlockHead(MyBlock *newBlock);
void insertBlockAfter(MyBlock *newBlock, MyBlock previousBlock);
void insertBlockTail(MyBlock *newBlock);
void freeBlock(MyBlock block);
MyBlock getNBlockInList(int nbBlock);

#endif // MY_MEMORY_H
