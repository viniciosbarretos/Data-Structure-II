#include <stdio.h>
#include <stdlib.h>
#include "memory.h"


// Create a memory node
Memory *newMemoryNode(unsigned size);

// Create a memory list.
MemoryList *newMemoryList() {
    MemoryList *memoryList = (MemoryList *) malloc(sizeof(MemoryList));
    memoryList->start = NULL;
    memoryList->end = NULL;
    return memoryList;
}

MemoryList *newMemory(unsigned size) {
    MemoryList *memoryList = newMemoryList();


}



