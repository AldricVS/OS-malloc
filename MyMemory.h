#ifndef MY_MEMORY_H
#define MY_MEMORY_H

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