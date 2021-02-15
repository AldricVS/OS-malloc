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
