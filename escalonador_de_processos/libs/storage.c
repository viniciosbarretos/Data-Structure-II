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
    if (!storageList->start) {
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

// Insert process at a list sorted by priority
StorageList* storageListInsertSorted(StorageList *storageList, Storage *storage) {

    // When list is NULL.
    if (!storageList->start) {
        storage->next = NULL;
        storage->prev = NULL;
        storageList->start = storage;
        storageList->end = storage;
    } else {
        // Search the position for the correct insertion.
        Storage *aux = storageList->start;
        while ((aux != NULL) && (aux->pcb->priority < storage->pcb->priority)) {
            aux = aux->next;
        }

        if (aux == NULL) { // Insert on the last position.
            storageList->end->next = storage;
            storage->prev = storageList->end;
            storageList->end = storage;
        } else if (aux->prev == NULL) { // Insert on the start.
            storage->next = storageList->start;
            storageList->start->prev = storage;
            storageList->start = storage;
        } else { // Insert on the middle.
            storage->prev = aux->prev;
            aux->prev->next = storage;
            storage->next = aux;
            aux->prev = storage;
        }

    }
    return storageList;
}

// To avoid starvation at jobs list
// this function rearrange old processes
// inserting them at start(end)
StorageList *storageListUpdatePriority(StorageList *storageList, unsigned int clock) {

    if (storageList != NULL) {
        Storage *aux = storageList->start;
        while (aux != NULL) {
            if (((clock - aux->pcb->creationTime) >= aux->pcb->quantum * 6) &&
                (aux->pcb->priority != 2)) {  //(possibly starvation : element with priority 2)
                aux->pcb->priority = 2;
                if (aux != storageList->end) {
                    if (aux == storageList->start) {
                        aux->next->prev = NULL;
                        storageList->start = aux->next;
                    } else {
                        aux->prev->next = aux->next;
                        aux->next->prev = aux->prev;
                    }

                    aux->next = NULL;
                    aux->prev = storageList->end;
                    storageList->end->next = aux;
                    storageList->end = aux;
                }
            }
            aux = aux->next;
        }
    }
    return storageList;
}


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

int moveFromScheduleToStorage(MemoryList **memory, ScheduleList **from, StorageList **to, unsigned int id, unsigned short status) {
    // Detach the element specified by id.
    Schedule *element = detachScheduleElement(from, id);

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
        (*to) = scheduleListInsertStart(*to, newSchedule(mem));

        // Remove our mem reference from memory.
        free(element);

        return id;
    }

    return -1;
}
