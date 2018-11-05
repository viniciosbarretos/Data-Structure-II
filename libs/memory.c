#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "pcb.h"

// Create a memory node.
Memory *newMemoryNode(unsigned int start, unsigned int size) {
    // Alloc memory.
    Memory *mem = (Memory *) malloc(sizeof(Memory));

    // Set values
    mem->size = size;
    mem->start = start;
    mem->pcb = NULL;

    // Return the node.
    return mem;
}

// Create the memory list.
MemoryList *newMemoryList() {
    MemoryList *memoryList = (MemoryList *) malloc(sizeof(MemoryList));
    memoryList->start = NULL;
    memoryList->end = NULL;
    return memoryList;
}

// Instantiate a memory.
MemoryList *newMemory(unsigned size) {
    // Create memory list.
    MemoryList *memoryList = newMemoryList();

    // Create the new node.
    Memory *mem = newMemoryNode(0, size);
    mem->next = NULL;
    mem->prev = NULL;

    // Insert the node on the list.
    memoryList->start = mem;
    memoryList->end = mem;

    return memoryList;
}

// Search for the node using bestFit.
Memory *getBestFitNode(MemoryList *memoryList, unsigned size) {
    // Search for smallest capable node size.
    Memory *aux = memoryList->start;
    Memory *min = NULL;
    while (aux) {
        if (!aux->pcb && size <= aux->size && (!min || aux->size < min->size)) {
            min = aux;
        }
        aux = aux->next;
    }

    // Return the node.
    return min;
}

// Allocate a new pcb in the memory.
Memory *memoryAlloc(MemoryList **memoryList, Memory *min, PCB *pcb) {
    unsigned size = pcb->size;

    // Create a index node for the pcb.

    min->pcb = pcb;
    // If the insertion generated a residue, put it on a new blank node.
    if (min->size - size > 0) {
        Memory *mem = newMemoryNode(min->start + size, min->size - size);
        // Re-point the nodes.
        mem->next = min->next;
        mem->prev = min;
        if (min->next) {
            min->next->prev = mem;
        }
        min->next = mem;

        // Check for the last index of the memory
        if (min == (*memoryList)->end) {
            (*memoryList)->end = mem;
        }
    }
    min->size = size;

        return min;
}

void *memoryFree(MemoryList **memory, Memory *mem) {
    // Delete pcb.
//    free(mem->pcb);
    mem->pcb = NULL;



    Memory *aux;
    // Merge memory with the previous node.
    if (mem->prev && !mem->prev->pcb) {
        aux = mem;
        mem = mem->prev;
        // Increase the size.
        mem->size += aux->size;
        // Re-point adjacent nodes.
        if (aux->next) {
            aux->next->prev = mem;
        }
        mem->next = aux->next;
        // Re-point list.
        if ((*memory)->end == aux) {
            (*memory)->end = mem;
        }
        // Remove node.
        free(aux);
    }

    // Merge memory with the next node.
    if (mem->next && !mem->next->pcb) {
        aux = mem->next;
        // Increase the size.
        mem->size += aux->size;
        // Re-point adjacent nodes.
        if (aux->next) {
            aux->next->prev = mem;
        }
        mem->next = aux->next;
        // Re-point list.
        if ((*memory)->end == aux) {
            (*memory)->end = mem;
        }
        // remove node.
        free(aux);
    }
}



