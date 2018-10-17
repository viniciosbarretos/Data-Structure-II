#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "pcb.h"

typedef struct List {
    struct PCB *start;
    struct PCB *end;
} List;

List * newList();
List * listInsertStart(List *list, PCB *pcb);
List * listInsertEnd(List *list, PCB *pcb);
List * listRemove(List *list);
List * listInsertSorted(List *list, PCB *pcb);
List * listUpdatePriority(List *list, unsigned int clock);

#endif //DATA_STRUCTURE_LIST_H
