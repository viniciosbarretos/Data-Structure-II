#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "pcb.h"

typedef struct List {
    struct PCB* front;
    struct PCB* back;
} List;

List * newList();
List * listInsert(List *list, PCB *pcb);
List * listRemove(List *list);
List * listInsertSorted(List *list, PCB *pcb);

#endif //DATA_STRUCTURE_LIST_H
