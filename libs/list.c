#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "pcb.h"

// Create the list pointers.
List * newList() {
    List * list = (List *) malloc(sizeof(PCB));
    list->front = NULL;
    list->back = NULL;

    return list;
}

// Insert an element in front of the list.
List * listInsert(List *list, PCB *pcb) {

    if (list->front == NULL) {
        pcb->next = NULL;
        list->front = pcb;
        list->back = pcb;
    } else {
        pcb->next = list->front;
    }

    return list;
}

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



