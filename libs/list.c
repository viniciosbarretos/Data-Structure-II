#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "pcb.h"

/*
 * List Scheme
 * 1 -> 2 -> 3 -> 4
 * Start          End
 */

// Create the list pointers.
List * newList() {
    List * list = (List *) malloc(sizeof(PCB));
    list->start = NULL;
    list->end = NULL;
    return list;
}

// Insert an element at start of the list
List * listInsertStart(List *list, PCB *pcb) {
    if (list->start == NULL) {
        pcb->next = NULL;
        list->start = pcb;
        list->end = pcb;
    } else {
        pcb->next = list->start;
        list->start = pcb;
    }
    return list;
}

// Insert an element at end of the list
List * listInsertEnd(List *list, PCB *pcb) {
    if (list->start == NULL) {
        list->start = pcb;
        list->end = pcb;
    } else {
        list->end->next = pcb;
        list->end = pcb;
    }
    return list;
}

// Insert process at a list sorted by priority
List * listInsertSorted(List *list, PCB *pcb) {
    
    if (list->start == NULL) {
        list->start = pcb;
        list->end = pcb;
    }
    else {
        PCB *prev = NULL;
        PCB *aux = list->start;
        while ( (aux != NULL) && (aux->priority >= pcb->priority) ) {
            prev = aux;
            aux = aux->next;
        }
        if (prev == NULL) {
            pcb->next = list->start;
            list->start = pcb;
        } else {
            prev->next = pcb;
            pcb->next = aux;
            if(aux == NULL)
                list->end = pcb;
        }
    }
    return list;
}


// To avoid starvation at jobs list
// this function rearange old processes
// inserting them at start
List * listUpdatePriority(List *list, unsigned int clock) {
    PCB *aux = list->start;
    PCB *prev = NULL;
    while (aux != NULL) {
        if ( ((clock - aux->creationTime) >= aux->quantum * 2) && (aux->priority != 2) ) {
            aux->priority = 2;
            if(aux != list->start) {
                prev->next = aux->next;
                if(prev->next == NULL)
                    list->end = prev;
                aux->next = list->start;
                list->start = aux;
            }
        }
        prev = aux;
        aux = aux->next;
    }
    return list;
}

/*
// Return the last but one element from a list.
PCB * _searchLastButOneElement(List *list) {
    PCB* aux = list->front;
    while (aux->next != NULL && aux->next != list->back) {
        aux = aux->next;
    }

    return aux;
}

// Remove the last element and re-point.
List * _removeLastElement(List *list) {
    PCB *aux = list->back;
    list->back = _searchLastButOneElement(list);
    list->back->next = NULL;
    free(aux);

    return list;
}

// Remove the remaining element from a queue.
List * _removeRemainingElement(List *list) {
    if (list->back != NULL) {
        free(list->back);
        list->front = NULL;
        list->back = NULL;
    }

    return list;
}

// Remove the last element from a queue.
List * listRemove(List *list) {
    if (list->front != list->back) {
        list = _removeLastElement(list);
    } else {
        list = _removeRemainingElement(list);
    }

    return list;
}



*/