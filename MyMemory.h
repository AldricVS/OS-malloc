#ifndef MY_MEMORY_H
#define MY_MEMORY_H

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

#endif // MY_MEMORY_H