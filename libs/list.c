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
List* newList() {
    List * list = (List *) malloc(sizeof(PCB));
    list->start = NULL;
    list->end = NULL;
    return list;
}

// Insert an element at start of the list
List* listInsertStart(List *list, PCB *pcb) {
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
List* listInsertEnd(List *list, PCB *pcb) {
    if (list->start == NULL) {
        pcb->next = NULL;
        list->start = pcb;
        list->end = pcb;
    } else {
        list->end->next = pcb;
        list->end = pcb;
    }
    return list;
}

// Insert process at a list sorted by priority
List* listInsertSorted(List *list, PCB *pcb) {
    
    if (list->start == NULL) {
        pcb->next = NULL;
        list->start = pcb;
        list->end = pcb;
    } else {
        PCB *prev = NULL;
        PCB *aux = list->start;

        while ( (aux != NULL) && (aux->priority < pcb->priority) ) {
            prev = aux;
            aux = aux->next;
        }

        if (prev == NULL) {
            pcb->next = list->start;
            list->start = pcb;
        } else {
            prev->next = pcb;
            pcb->next = aux;
            if (aux == NULL)
                list->end = pcb;
        }
    }
    return list;
}

unsigned int listCounter(List* list) {
    unsigned int counter = 0;

    // Counter the elements of the list.
    PCB *aux = list->start;
    while (aux != NULL) {
        counter++;
        aux = aux->next;
    }

    return counter;
}

// To avoid starvation at jobs list
// this function rearrange old processes
// inserting them at start
List* listUpdatePriority(List* list, unsigned int clock) {
    if(list != NULL) {
        PCB *aux = list->start;
        PCB *prev = NULL;
        while (aux != NULL) {
            if (((clock - aux->creationTime) >= aux->quantum * 6) && (aux->priority != 2)) {
                aux->priority = 2;
                if (aux != list->end) {
                    if (aux == list->start)
                        list->start = aux->next;
                    else
                        prev->next = aux->next;

                    aux->next = NULL;
                    list->end->next = aux;
                    list->end = aux;
                }
            }
            prev = aux;
            aux = aux->next;
        }
    }
    return list;
}

// Return an element from a list and re-point the elements.
PCB* _detachElement(List** list, unsigned int targetId) {
    // Empty list.
    if ((*list)->start == NULL) return NULL;

    // Search the element.
    PCB *aux = (*list)->start;
    PCB *prev = NULL;
    while ( (aux->next != NULL) && (aux->id != targetId) ) {
        prev = aux;
        aux = aux->next;
    }

    // Detach the element and re-point.
    if (aux->id == targetId) {
        // Detach the last only list element.
        if (prev == NULL && aux->next == NULL) {
            (*list)->start = NULL;
            (*list)->end = NULL;
        }
        // Detach the first element.
        else if (prev == NULL) {
            (*list)->start = (*list)->start->next;
        }
        // Detach an middle element.
        else if (aux->next != NULL) {
            prev->next = aux->next;
        }
        // Detach the last element.
        else {
            prev->next = NULL;
            (*list)->end = prev;
        }

        // Clean element.
        aux->next = NULL;
    }
    // Element not found.
    else {
        aux = NULL;
    }

    return aux;
}

PCB* _detachLastElement(List** list) {
    return _detachElement(list, (*list)->end->id);
}

// Remove the last element from a queue.
List* listRemove(List *list) {
    if (list->start == NULL) return list; // Nothing to remove.

    // Get last element and delete.
    free(_detachLastElement(&list));

    return list;
}

int moveElementBetweenLists(List **from, List **to, unsigned int id, unsigned short status) {
    if ((*from)->start == NULL) return 0; // Impossible to move from a null list.

    // Detach the element specified by id.
    PCB *element = _detachElement(from, id);

    // Set new status to pbc.
    element->status = status;

    // Insert element into the new list.
    (*to) = listInsertStart(*to, element);

    return 1;
}

int moveBetweenLists(List **from, List **to, unsigned short status) {
    if ((*from)->end == NULL) return 0;
    return moveElementBetweenLists(from, to, (*from)->end->id, status);
}

