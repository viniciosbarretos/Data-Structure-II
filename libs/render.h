#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "pcb.h"
#include "list.h"

char* getStatus(int status, int id);
void renderElement(PCB *pcb);
void renderList(List *list);
void renderScreen(List* jobs, List* ready, List* blocked, List* finished, List* cpu, unsigned int clock,
                  unsigned int time, char* action);

#endif //DATA_STRUCTURE_RENDER_H
