#include <stdio.h>
#include <stdlib.h>
#include "schedule.h"
#include "pcb.h"

/*
 * ScheduleList Scheme
 * 1 -> 2 -> 3 -> 4
 * Start          End
 */

// Create the list pointers.
ScheduleList *newList() {
    ScheduleList *scheduleList = (ScheduleList *) malloc(sizeof(ScheduleList));
    scheduleList->start = NULL;
    scheduleList->end = NULL;
    return scheduleList;
}

// Insert an element at the start of the list
ScheduleList *listInsertStart(ScheduleList *scheduleList, Schedule *schedule) {
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;
        scheduleList->start = schedule;
        scheduleList->end = schedule;
    } else {
        schedule->next = scheduleList->start;
        schedule->prev = NULL;
        scheduleList->start->prev = schedule;
        scheduleList->start = schedule;
    }
    return scheduleList;
}

// Insert an element at the end of the list
ScheduleList *listInsertEnd(ScheduleList *scheduleList, Schedule *schedule) {
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;
        scheduleList->start = schedule;
        scheduleList->end = schedule;
    } else {
        schedule->next = NULL;
        schedule->prev = scheduleList->end;
        scheduleList->end->next = schedule;
        scheduleList->end = schedule;
    }
    return scheduleList;
}

// Insert process at a list sorted by priority
ScheduleList *listInsertSorted(ScheduleList *scheduleList, Schedule *schedule) {

    // Check if the list has no elements.
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;
        scheduleList->start = schedule;
        scheduleList->end = schedule;

        return scheduleList;
    }

    // Search for the schedule node position by priority.
    Schedule *aux = scheduleList->start;
    while ((aux != NULL) && (aux->memory->pcb->priority < schedule->memory->pcb->priority)) {
        aux = aux->next;
    }

    // Make insertion.
    if (aux == NULL) { // Insertion on the end.
        schedule->prev = scheduleList->end;
        scheduleList->end->next = schedule;
        scheduleList->end = schedule;

    } else if (aux->prev == NULL) { // Insertion in the start.
        schedule->next = scheduleList->start;
        scheduleList->start->prev = schedule;
        scheduleList->start = schedule;

    } else { // Insertion at the middle.
        schedule->prev = aux->prev;
        schedule->next = aux;
        aux->prev->next = schedule;
        aux->prev = schedule;
    }

    return scheduleList;
}

unsigned int listCounter(ScheduleList *scheduleList) {
    unsigned int counter = 0;

    // Counter the elements of the schedule list.
    Schedule *aux = scheduleList->start;
    while (aux != NULL) {
        counter++;
        aux = aux->next;
    }

    return counter;
}

// To avoid starvation at jobs list
// this function rearrange old processes
// inserting them at start(end)
ScheduleList *listUpdatePriority(ScheduleList *scheduleList, unsigned int clock) {
    if (scheduleList != NULL) {
        Schedule *aux = scheduleList->start;
        Schedule *prev = NULL;
        while (aux != NULL) {
            if (((clock - aux->memory->pcb->creationTime) >= aux->memory->pcb->quantum * 6) &&
                (aux->memory->pcb->priority != 2)) {  //(possibly starvation : element with priority 2)
                aux->memory->pcb->priority = 2;
                if (aux != scheduleList->end) {
                    if (aux == scheduleList->start) {
                        aux->next->prev = NULL;
                        scheduleList->start = aux->next;
                    } else {
                        aux->prev->next = aux->next;
                        aux->next->prev = aux->prev;
                    }

                    aux->next = NULL;
                    aux->prev = scheduleList->end;
                    scheduleList->end->next = aux;
                    scheduleList->end = aux;
                }
            }
            prev = aux;
            aux = aux->next;
        }
    }
    return scheduleList;
}

// Return an element from a list and re-point the elements.
Schedule *_detachElement(ScheduleList **scheduleList, unsigned int targetId) {
    // Empty schedule List.
    if ((*scheduleList)->start == NULL) return NULL;

    // Search the element.
    Schedule *aux = (*scheduleList)->start;
    while ((aux->next != NULL) && (aux->memory->pcb->id != targetId))
        aux = aux->next;


    // Detach the element and re-point.
    if (aux->memory->pcb->id == targetId) {
        // Detach the last only schedule list element.
        if (aux->prev == NULL && aux->next == NULL) {
            (*scheduleList)->start = NULL;
            (*scheduleList)->end = NULL;
        }
            // Detach the first element.
        else if (aux->prev == NULL) {
            (*scheduleList)->start = (*scheduleList)->start->next;
            (*scheduleList)->start->prev = NULL;
        }
            // Detach an middle element.
        else if (aux->next != NULL) {
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
        }
            // Detach the last element.
        else {
            aux->prev->next = NULL;
            (*scheduleList)->end = aux->prev;
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

Schedule *_detachLastElement(ScheduleList **scheduleList) {
    return _detachElement(scheduleList, (*scheduleList)->end->memory->pcb->id);
}

// Remove the last element from a queue.
ScheduleList *listRemove(ScheduleList *scheduleList) {
    if (scheduleList->start == NULL) return scheduleList; // Nothing to remove.

    // Get last element and delete.
    free(_detachLastElement(&scheduleList));

    return scheduleList;
}

int moveElementBetweenLists(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status) {
    if ((*from)->start == NULL) return 0; // Impossible to move from a null list.

    // Detach the element specified by id.
    Schedule *element = _detachElement(from, id);

    // Set new status to pbc.
    element->memory->pcb->status = status;

    // Insert element into the new list.
    (*to) = listInsertStart(*to, element);

    return 1;
}

int moveBetweenLists(ScheduleList **from, ScheduleList **to, unsigned short status) {
    if ((*from)->end == NULL) return 0;
    return moveElementBetweenLists(from, to, (*from)->end->memory->pcb->id, status);
}

int isEmpty(ScheduleList **scheduleList) {
    return (*scheduleList)->start == NULL;
}