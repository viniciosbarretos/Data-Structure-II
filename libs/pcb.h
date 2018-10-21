#ifndef DATA_STRUCTURE_PCB_H
#define DATA_STRUCTURE_PCB_H

#define _pcbStatusNew      0
#define _pcbStatusReady    1
#define _pcbStatusRunning  2
#define _pcbStatusBlocked  3
#define _pcbStatusDone     4

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
