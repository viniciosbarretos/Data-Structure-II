#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

PCB * newPcb() {
    PCB *pcb = (PCB *) malloc(sizeof(PCB));
    return pcb;
}

