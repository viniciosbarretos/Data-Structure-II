#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

//Creates 38% rate for process interruption
unsigned int _interruptionGenerator(unsigned int quantum) {

    unsigned int interruption;
    unsigned int willStop;

    willStop = rand() % 101;
    if(willStop >= 38)
        willStop = 1;
    else
        willStop = 0;

    //This is about 38% likely to happen, it`s possible only one interruption for process - needs to review
    if(willStop)
        interruption = 1 + ( rand() % (quantum-1) );

    return interruption;
}

// Create the pointer for a PCB
PCB * newPCB(unsigned int *id, unsigned int creationTime) {
    PCB *pcb = (PCB *) malloc(sizeof(PCB));
    pcb->id = (*id)++;
    pcb->quantum = rand() % 200 + 1;
    pcb->priority = rand() % 3;
    pcb->status = 0;
    pcb->interruption = _interruptionGenerator(pcb->quantum);
    pcb->next = NULL;
    pcb->startProcessingTime = 0;
    pcb->endProcessingTime = 0;
    pcb->creationTime = creationTime;
    pcb->waitTime = 0;
    return pcb;
}

