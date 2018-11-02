#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "pcb.h"
#include "schedule.h"

/*
 * ScheduleList Scheme
 * 1 -> 2 -> 3 -> 4
 * Start          End
 */

// Create the list pointers.
ScheduleList* newList() {
    ScheduleList * scheduleList = (ScheduleList *) malloc(sizeof(Schedule));
    scheduleList->start = NULL;
    scheduleList->end = NULL;
    return scheduleList;
}

// Insert an element at start of the list
ScheduleList* listInsertStart(ScheduleList *scheduleList, Schedule *schedule) {
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;                   //update
        scheduleList->start = schedule;
        scheduleList->end = schedule;
    } else {
        schedule->next = scheduleList->start;
        scheduleList->start->prev = schedule;    //update
        schedule->prev = NULL;                   //update
        scheduleList->start = schedule;
    }
    return scheduleList;
}

// Insert an element at end of the list
ScheduleList* listInsertEnd(ScheduleList *scheduleList, Schedule *schedule) {
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;                   //update
        scheduleList->start = schedule;
        scheduleList->end = schedule;
    } else {
        scheduleList->end->next = schedule;
        schedule->prev = scheduleList->end;    //update
        schedule->next = NULL;                 //update
        scheduleList->end = schedule;
    }
    return scheduleList;
}

// Insert process at a list sorted by priority
ScheduleList* listInsertSorted(ScheduleList *scheduleList, Schedule *schedule) {
    
    if (scheduleList->start == NULL) {
        schedule->next = NULL;
        schedule->prev = NULL;                  //update
        scheduleList->start = schedule;
        scheduleList->end = schedule;
    } else {
        Schedule *aux = scheduleList->start;

        while ( (aux != NULL) && (aux->memory->pcb->priority < schedule->memory->pcb->priority) )
            aux = aux->next;

        if (aux == NULL) {
            scheduleList->end->next = schedule;             //update
            schedule->prev = scheduleList->end;             //update
            scheduleList->end = schedule;                   //update
        } else {
            if (aux->prev == NULL) {                        //update
                schedule->next = scheduleList->start;       //update
                scheduleList->start->prev = schedule;       //update
                scheduleList->start = schedule;             //update
            } else {
                schedule->prev = aux->prev;                 //update
                aux->prev->next = schedule;                 //update
                schedule->next = aux;                       //update
                aux->prev = schedule;                       //update
            }

    }
    return scheduleList;
}

unsigned int listCounter(ScheduleList* scheduleList) {
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
ScheduleList* listUpdatePriority(ScheduleList* scheduleList, unsigned int clock) {
    if(scheduleList != NULL) {
        Schedule *aux = scheduleList->start;
        Schedule *prev = NULL;
        while (aux != NULL) {
            if (((clock - aux->memory->pcb->creationTime) >=aux->memory->pcb->quantum * 6) && (aux->memory->pcb->priority != 2)) {  //(possibly starvation : element with priority 2)
                aux->memory->pcb->priority = 2;
                if (aux != scheduleList->end) {
                    if (aux == scheduleList->start) {
                        aux->next->prev = NULL;             //update
                        scheduleList->start = aux->next;
                    }
                    else {
                        aux->prev->next = aux->next;        //update
                        aux->next->prev = aux->prev;        //update
                    }

                    aux->next = NULL;
                    aux->prev = scheduleList->end;          //update
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
Schedule* _detachElement(ScheduleList** scheduleList, unsigned int targetId) {
    // Empty schedule List.
    if ((*scheduleList)->start == NULL) return NULL;

    // Search the element.
    PCB *aux = (*scheduleList)->start;
    while ( (aux->next != NULL) && (aux->id != targetId) )
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
            (*scheduleList)->start->prev = NULL;            //update
        }
        // Detach an middle element.
        else if (aux->next != NULL) {
            aux->prev->next = aux->next;                    //update
            aux->next->prev = aux->prev;                    //update
        }
        // Detach the last element.
        else {
            aux->prev->next = NULL;                         //update
            (*scheduleList)->end = prev;
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

Schedule* _detachLastElement(ScheduleList** scheduleList) {
    return _detachElement(scheduleList, (*scheduleList)->end->memory->pcb->id);
}

// Remove the last element from a queue.
ScheduleList* listRemove(ScheduleList *scheduleList) {
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

