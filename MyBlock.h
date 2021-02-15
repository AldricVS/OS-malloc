#ifndef MY_BLOCK_H
#define MY_BLOCK_H

typedef struct myBlockCel {
	unsigned int contentSize;
	void *contentPtr;
	struct myBlockCel *nextBlock;
}*MyBlock;

void *myAlloc(int nBytes);
int myFree(void *contentPtr);

#endif
