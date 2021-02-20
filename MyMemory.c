#include "MyMemory.h"
#include <stdlib.h>

MyMemory memory;

int initMemory(int nBytes) {
    // Allocate nBytes bytes (char == 1 byte)
    void *ptr = malloc(nBytes * sizeof(char));
    if (ptr == NULL) {
        return -1;
    }
    else {
        // Init memory and return the number of bytes allocated
        memory.size = nBytes;
        memory.isFree = 0;
        memory.array = ptr;
        memory.firstBlock = NULL;
        memory.lastBlock = NULL;
        return nBytes;
    }
}

int freeMemory() {
    // We can't free memory multiple times
    if (memory.isFree) {
        return -1;
    }
    else {
        memory.isFree = 1;
        free(memory.array);
        return memory.size;
    }
}

void insertBlockHead(MyBlock newBlock) {
    MyBlock firstBlock = memory.firstBlock;
    newBlock->nextBlock = firstBlock;
    firstBlock = newBlock;
}

void insertBlockAfter(MyBlock newBlock, MyBlock previousBlock) {
    MyBlock afterBlock = previousBlock->nextBlock;
    previousBlock->nextBlock = newBlock;
    newBlock->nextBlock = afterBlock;
}

void insertBlockTail(MyBlock newBlock) {
    MyBlock lastBlock = memory.lastBlock;
    lastBlock->nextBlock = newBlock;
    newBlock->nextBlock = NULL;
}
