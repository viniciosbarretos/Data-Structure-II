//
// Created by vino on 11/2/2018.
//
#include <stdlib.h>
#include "pcb.h"

#ifndef DATA_STRUCTURE_MEMORY_H
#define DATA_STRUCTURE_MEMORY_H

//Tamanho máximo 128w (Endereçamento de 0 até 127)
typedef struct Memory {
    struct PCB *pcb;
    unsigned int start, size;
    struct Memory *next, *prev;
} Memory;

typedef struct MemoryList {
    struct Memory *start;
    struct Memory *end;
} MemoryList;

MemoryList *newMemory(unsigned size);
Memory *memoryAlloc(MemoryList **memoryList, Memory *min, PCB *pcb);
void *memoryFree(MemoryList **memory, Memory *mem);
Memory *getBestFitNode(MemoryList *memoryList, unsigned size);

#endif //DATA_STRUCTURE_MEMORY_H