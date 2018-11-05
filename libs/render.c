#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "storage.h"
#include "schedule.h"
#include "memory.h"

char* strCopy(char* out, const char* src) {
    unsigned int i;
    for (i=0; src[i] != '\0'; i++) {
        out[i] = src[i];
    }

    // Define the end of str.
    out[i] = '\0';

    return out;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char* getStatus(int status, int id) {
    char *str = (char*) malloc(sizeof(char) * 64);

    switch (status) {
        case 0: sprintf(str, "Nothing happens"); break;
        case 1: sprintf(str, "Process %d dispatched", id); break;
        case 2: sprintf(str, "Process %d interrupted", id); break;
        case 3: sprintf(str, "Process %d I/O wait", id); break;
        case 4: sprintf(str, "Process %d exited", id); break;
        case 5: sprintf(str, "Process %d I/O completed", id); break;
        case 6: sprintf(str, "Process %d admitted", id); break;
        case 7: sprintf(str, "Process %d created", id); break;
        default: sprintf(str, "I do not know");
    }

    return str;
}

/*
 * Schedule
 */

void renderElement(Schedule *schedule) {
    if (schedule) {
        printf(" ID: [%4d ]\n", schedule->memory->pcb->id);
        printf(" QU: [%4d ] ", schedule->memory->pcb->quantum - schedule->memory->pcb->lineCounter);
    }
}

void renderId(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;

    printf("ID: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->memory->pcb->id);
        aux = aux->next;
        maxElements--;
    }
}

void renderQuantum(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;

    printf("QU: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->memory->pcb->quantum - aux->memory->pcb->lineCounter);
        aux = aux->next;
        maxElements--;
    }
}

void renderPriority(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;

    printf("PR: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->memory->pcb->priority);
        aux = aux->next;
        maxElements--;
    }
}

/*
 * Storage
 */

void renderStorageId(StorageList *storageList, int maxElements) {
    Storage *aux = storageList->start;

    printf("ID: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->pcb->id);
        aux = aux->next;
        maxElements--;
    }
}

void renderStoragePriority(StorageList *storageList, int maxElements) {
    Storage *aux = storageList->start;

    printf("PR: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->pcb->priority);
        aux = aux->next;
        maxElements--;
    }
}

void renderProcessingTime(StorageList *storageList, int maxElements) {
    Storage *aux = storageList->start;

    printf("ET: ");
    while (aux && maxElements) {
        printf("[%4d ] ", (aux->pcb->endProcessingTime - aux->pcb->startProcessingTime) + 1);
        aux = aux->next;
        maxElements--;
    }
}

void renderInitialQuantum(StorageList *storageList, int maxElements) {
    Storage *aux = storageList->start;

    printf("QU: ");
    while (aux && maxElements) {
        printf("[%4d ] ", aux->pcb->quantum);
        aux = aux->next;
        maxElements--;
    }
}

void renderScheduleList(ScheduleList *scheduleList, int maxElements) {

    if (!scheduleList->start)
        printf("Empty scheduleList!\n");
    else {
        renderId(scheduleList, maxElements);
        printf("\n");
        renderPriority(scheduleList, maxElements);
        printf("\n");
        renderQuantum(scheduleList, maxElements);
        printf("\n");
    }
}

void renderListJobs(StorageList *list, int maxElements) {
    if (!list->start)
        printf("Empty list!\n");
    else {
        renderStorageId(list, maxElements);
        printf("\n");
        renderStoragePriority(list, maxElements);
        printf("\n");
        renderInitialQuantum(list, maxElements);
        printf("\n");
    }
}

void renderListFinished(StorageList *list, int maxElements) {
    if (!list->start)
        printf("Empty list!\n");
    else {
        renderStorageId(list, maxElements);
        printf("\n");
        renderProcessingTime(list, maxElements);
        printf("\n");
        renderInitialQuantum(list, maxElements);
        printf("\n");
    }
}

void renderMemoryNode(Memory *node) {
    if (!node->pcb) {
        printf("[ NULL | %3d | %3d ]", node->start, node->size);
    } else {
        printf("[ %4d | %3d | %3d ]", node->pcb->id, node->start, node->size);
    }
}

void renderMemoryList(MemoryList *list) {
    Memory *aux = list->start;
    while (aux) {
        renderMemoryNode(aux);

        if (aux->next) {
            printf(" -> ");
        }

        aux = aux->next;
    }
    printf ("\n");
}



void renderScreen(MemoryList *memoryList, StorageList* jobs, ScheduleList* ready, ScheduleList* blocked, StorageList* finished, ScheduleList* cpu, unsigned int clock,
                  unsigned int time, char* action) {
    // Clear screen.
    clearScreen();

    // Printing memory.
    printf("Memory: \n");
    renderMemoryList(memoryList);

    // Printing lists.
    printf("Jobs:       \n");
    renderListJobs(jobs, -1);
    printf("\nReady:    \n");
    renderScheduleList(ready, -1);
    printf("\nBlocked:  \n");
    renderScheduleList(blocked, -1);
    printf("\nFinished: \n");
    renderListFinished(finished, 12);

    // Printing the additional data.
    printf("\n----------------------------------------");
    printf("\nClock: %d", (int) clock);
    printf("\tElapsed Clock: %d", (int) time);
    printf("\n\nProcessing:\n");
    renderElement(cpu->start);
    printf("\n\nAction: %s\n", action);
    printf("<<===================================================================================>>\n");
}
