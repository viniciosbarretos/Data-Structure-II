//
// Created by vino on 11/2/2018.
//
#include <stdlib.h>
#ifndef DATA_STRUCTURE_MEMORY_H
#define DATA_STRUCTURE_MEMORY_H

//Tamanho máximo 128w (Endereçamento de 0 até 127)
typedef struct Memory {
    struct PCB *pcb;
    int start, size;
    struct Memory *next, *prev;
} Memory;

typedef struct MemoryList {
    struct Memory *start;
    struct Memory *end;
} MemoryList;

#endif //DATA_STRUCTURE_MEMORY_H