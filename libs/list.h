#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "pcb.h"

typedef struct List {
    struct PCB *start;
    struct PCB *end;
} List;

List* newList();
List* listInsertStart(List *list, PCB *pcb);
List* listInsertEnd(List *list, PCB *pcb);
List* listRemove(List *list);
List* listInsertSorted(List *list, PCB *pcb);
List* listUpdatePriority(List *list, unsigned int clock);
int moveBetweenLists(List **from, List **to, unsigned short status);
int moveElementBetweenLists(List **from, List **to, unsigned int id, unsigned short status);
unsigned int listCounter(List* list);
int isEmpty(List **list);


#endif //DATA_STRUCTURE_LIST_H
