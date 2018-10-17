#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

// Create the pointer for a PCB
PCB * newPCB(int *id) {
    PCB *pcb = (PCB *) malloc(sizeof(PCB));
    pcb->id = (*id)++;
    pcb->quantum = rand() % 200 + 1;
    pcb->priority = rand() % 3;
    pcb->status = 0;
    pcb->interruption = rand() % (pcb->quantum) + 1;
    pcb->next = NULL;
    pcb->startProcessingTime = 0;
    pcb->endProcessingTime = 0;
    pcb->waitTime = 0;
    return pcb;
}

