#ifndef DATA_STRUCTURE_PCB_H
#define DATA_STRUCTURE_PCB_H

typedef struct PCB {
    struct PCB *next;
    unsigned int id;
    unsigned int quantum;
    unsigned short int priority;
    unsigned short int status;
    unsigned int interruption;
    unsigned int startProcessingTime;
    unsigned int endProcessingTime;
    unsigned int waitTime;
} PCB;

PCB * newPCB(int *id);

#endif //DATA_STRUCTURE_PCB_H
