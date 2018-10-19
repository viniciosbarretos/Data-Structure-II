#ifndef DATA_STRUCTURE_PCB_H
#define DATA_STRUCTURE_PCB_H

typedef struct PCB {
    struct PCB *next;
    unsigned int id;
    unsigned int quantum;
    unsigned int lineCounter;
    unsigned short int priority;
    unsigned short int status;
    unsigned int interruption;
    unsigned int startProcessingTime;
    unsigned int endProcessingTime;
    unsigned int creationTime;
    unsigned int waitTime;
} PCB;

PCB* generatePCB(unsigned int id, unsigned int creationTime);
PCB* getWaitTime(PCB* pcb);

#endif //DATA_STRUCTURE_PCB_H
