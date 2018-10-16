#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

// Create the pointer for a PCB
PCB * newPcb() {
    PCB *pcb = (PCB *) malloc(sizeof(PCB));
    return pcb;
}

