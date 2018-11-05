#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "pcb.h"
#include "schedule.h"
#include "memory.h"
#include "rand.h"

/*
 * ScheduleList Scheme
 * 1 -> 2 -> 3 -> 4
 * Start          End
 */

//StorageList* newStorageList();
//StorageList* storageListInsertStart(StorageList *pcbList, PCB *pcb);
//StorageList* storageListInsertSorted(StorageList *pcbList, PCB *pcb);
//StorageList* storageListUpdatePriority(StorageList *pcbList, unsigned int clock);

// Create the list pointers.
StorageList* newStorageList() {
    StorageList *storageList = (StorageList*) malloc(sizeof(StorageList));
    storageList->start = NULL;
    storageList->end = NULL;
    return storageList;
}

Storage *newStorage(PCB *pcb) {
    Storage *storage = (Storage*) malloc(sizeof(Storage));
    storage->pcb = pcb;

    return storage;
}

// Insert an element at start of the list
StorageList* storageListInsertStart(StorageList *storageList, Storage *storage) {
    if (storageList->start == NULL) {
        storage->next = NULL;
        storage->prev = NULL;
        storageList->start = storage;
        storageList->end = storage;
    } else {
        storage->next = storageList->start;
        storage->prev = NULL;
        storageList->start->prev = storage;
        storageList->start = storage;
    }
    return storageList;
}

//// Insert an element at end of the list
//ScheduleList* listInsertEnd(ScheduleList *scheduleList, Schedule *schedule) {
//    if (scheduleList->start == NULL) {
//        schedule->next = NULL;
//        schedule->prev = NULL;                   //update
//        scheduleList->start = schedule;
//        scheduleList->end = schedule;
//    } else {
//        scheduleList->end->next = schedule;
//        schedule->prev = scheduleList->end;    //update
//        schedule->next = NULL;                 //update
//        scheduleList->end = schedule;
//    }
//    return scheduleList;
//}

//// Insert process at a list sorted by priority
//ScheduleList* listInsertSorted(ScheduleList *scheduleList, Schedule *schedule) {
//
//    if (scheduleList->start == NULL) {
//        schedule->next = NULL;
//        schedule->prev = NULL;                  //update
//        scheduleList->start = schedule;
//        scheduleList->end = schedule;
//    } else {
//        Schedule *aux = scheduleList->start;
//
//        while ((aux != NULL) && (aux->memory->pcb->priority < schedule->memory->pcb->priority))
//            aux = aux->next;
//
//        if (aux == NULL) {
//            scheduleList->end->next = schedule;             //update
//            schedule->prev = scheduleList->end;             //update
//            scheduleList->end = schedule;                   //update
//        } else {
//            if (aux->prev == NULL) {                        //update
//                schedule->next = scheduleList->start;       //update
//                scheduleList->start->prev = schedule;       //update
//                scheduleList->start = schedule;             //update
//            } else {
//                schedule->prev = aux->prev;                 //update
//                aux->prev->next = schedule;                 //update
//                schedule->next = aux;                       //update
//                aux->prev = schedule;                       //update
//            }
//
//        }
//        return scheduleList;
//    }
//}
//
//    unsigned int listCounter(ScheduleList *scheduleList) {
//        unsigned int counter = 0;
//
//        // Counter the elements of the schedule list.
//        Schedule *aux = scheduleList->start;
//        while (aux != NULL) {
//            counter++;
//            aux = aux->next;
//        }
//
//        return counter;
//    }
//
//// To avoid starvation at jobs list
//// this function rearrange old processes
//// inserting them at start(end)
//    ScheduleList *listUpdatePriority(ScheduleList *scheduleList, unsigned int clock) {
//        if (scheduleList != NULL) {
//            Schedule *aux = scheduleList->start;
//            Schedule *prev = NULL;
//            while (aux != NULL) {
//                if (((clock - aux->memory->pcb->creationTime) >= aux->memory->pcb->quantum * 6) &&
//                    (aux->memory->pcb->priority != 2)) {  //(possibly starvation : element with priority 2)
//                    aux->memory->pcb->priority = 2;
//                    if (aux != scheduleList->end) {
//                        if (aux == scheduleList->start) {
//                            aux->next->prev = NULL;             //update
//                            scheduleList->start = aux->next;
//                        } else {
//                            aux->prev->next = aux->next;        //update
//                            aux->next->prev = aux->prev;        //update
//                        }
//
//                        aux->next = NULL;
//                        aux->prev = scheduleList->end;          //update
//                        scheduleList->end->next = aux;
//                        scheduleList->end = aux;
//                    }
//                }
//                prev = aux;
//                aux = aux->next;
//            }
//        }
//        return scheduleList;
//    }
//

Storage *searchElementOnStorage(StorageList *list, unsigned int targetId) {
    // Search the element.
    Storage *aux = list->start;
    while (aux && aux->pcb->id != targetId) {
        aux = aux->next;
    }

    return aux;
}

Storage *detachStorageElement(StorageList **list, Storage *element) {
    // Detach the element and re-point
    if (element) {
        // Detach the last only storage list element.
        if (!element->prev && !element->next) {
            (*list)->start = NULL;
            (*list)->end = NULL;
        }
        // Detach the first element
        else if (!element->prev) {
            (*list)->start = element->next;
            (*list)->start->prev = NULL;
        }
        // Detach an middle element
        else if (element->next) {
            element->prev->next = element->next;
            element->next->prev = element->prev;
        }
        // Detach the last element.
        else {
            (*list)->end = element->prev;
            (*list)->end->next = NULL;
        }

        // Clean the element
        element->next = NULL;
        element->prev = NULL;
    } else {
        element = NULL;
    }

    return element;
}

//// Return an element from a list and re-point the elements.
//    Schedule *detachElement(ScheduleList **scheduleList, unsigned int targetId) {
//        // Empty schedule List.
//        if ((*scheduleList)->start == NULL) return NULL;
//
//        // Search the element.
//        Schedule *aux = (*scheduleList)->start;
//        while ((aux->next != NULL) && (aux->memory->pcb->id != targetId))
//            aux = aux->next;
//
//
//        // Detach the element and re-point.
//        if (aux->memory->pcb->id == targetId) {
//            // Detach the last only schedule list element.
//            if (aux->prev == NULL && aux->next == NULL) {
//                (*scheduleList)->start = NULL;
//                (*scheduleList)->end = NULL;
//            }
//                // Detach the first element.
//            else if (aux->prev == NULL) {
//                (*scheduleList)->start = (*scheduleList)->start->next;
//                (*scheduleList)->start->prev = NULL;            //update
//            }
//                // Detach an middle element.
//            else if (aux->next != NULL) {
//                aux->prev->next = aux->next;                    //update
//                aux->next->prev = aux->prev;                    //update
//            }
//                // Detach the last element.
//            else {
//                aux->prev->next = NULL;                         //update
//                (*scheduleList)->end = aux->prev;
//            }
//
//            // Clean element.
//            aux->next = NULL;
//        }
//            // Element not found.
//        else {
//            aux = NULL;
//        }
//
//        return aux;
//    }
//
//    Schedule *_detachLastElement(ScheduleList **scheduleList) {
//        return detachElement(scheduleList, (*scheduleList)->end->memory->pcb->id);
//    }
//
//// Remove the last element from a queue.
//    ScheduleList *listRemove(ScheduleList *scheduleList) {
//        if (scheduleList->start == NULL) return scheduleList; // Nothing to remove.
//
//        // Get last element and delete.
//        free(_detachLastElement(&scheduleList));
//
//        return scheduleList;
//    }
//
//    int moveElementBetweenLists(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status) {
//        if ((*from)->start == NULL) return 0; // Impossible to move from a null list.
//
//        // Detach the element specified by id.
//        Schedule *element = detachElement(from, id);
//
//        // Set new status to pbc.
//        element->memory->pcb->status = status;
//
//        // Insert element into the new list.
//        (*to) = listInsertStart(*to, element);
//
//        return 1;
//    }
//
//    int moveBetweenLists(ScheduleList **from, ScheduleList **to, unsigned short status) {
//        if ((*from)->end == NULL) return 0;
//        return moveElementBetweenLists(from, to, (*from)->end->memory->pcb->id, status);
//    }
//
//    int isEmpty(ScheduleList **scheduleList) {
//        return (*scheduleList)->start == NULL;
//    }

int moveFromScheduleToStorage(MemoryList **memory, ScheduleList **from, StorageList **to, unsigned int id, unsigned short status) {
    // Detach the element specified by id.
    Schedule *element = detachElement(from, id);

    // Set the new status to pcb.
    element->memory->pcb->status = status;

    // Insert element into the new list.
    (*to) = storageListInsertStart(*to, newStorage(element->memory->pcb));

    // Remove pcb from memory.
    memoryFree(memory, element->memory);

    // Remove element from memory.
//    free(element);

    return id;
}

int moveFromStorageToSchedule(MemoryList **memory, StorageList **from, ScheduleList **to, unsigned int id, unsigned short status) {
    // Get element with it id.
    Storage *element = searchElementOnStorage(*from, id);

    // Get the best allocation node
    Memory *mem = getBestFitNode(*memory, element->pcb->size);

    // If memory has a space for the process.
    if (mem) {
        // Detach the element
        element = detachStorageElement(from, element);

        // Set the new status to pcb
        element->pcb->status = status;

        // Allocate memory.
        mem = memoryAlloc(memory, mem, element->pcb);

        // insert the memory process reference on the schedule list.
        (*to) = listInsertStart(*to, newSchedule(mem));

        // Remove our mem reference from memory.
        free(element);

        return id;
    }

    return -1;
}
