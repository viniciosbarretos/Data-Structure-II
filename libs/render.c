#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "list.h"
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

void renderElement(Schedule *schedule) {
    if (schedule != NULL) {
        printf(" ID: [%4d%1s]\n", schedule->memory->pcb->id, "");
        printf("%12sQU: [%4d%1s] ", "", schedule->memory->pcb->quantum - schedule->memory->pcb->lineCounter, "");
    }
}

void renderProcessingTime(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;
    int count = 0;

    printf("ET: ");
    if(maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", (aux->memory->pcb->startProcessingTime - aux->memory->pcb->startProcessingTime) + 1, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", (aux->memory->pcb->endProcessingTime - aux->memory->pcb->startProcessingTime) + 1, "");
            aux = aux->next;
        }
    }
}

void renderId(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;
    int count = 0;

    printf("ID: ");
    if(maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->memory->pcb->id, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->memory->pcb->id, "");
            aux = aux->next;
        }
    }
}

void renderInitialQuantum(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;
    int count = 0;

    printf("QU: ");
    if (maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->memory->pcb->quantum, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->memory->pcb->quantum, "");
            aux = aux->next;
        }
    }
}

void renderQuantum(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;
    int count = 0;

    printf("QU: ");
    if (maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->memory->pcb->quantum - aux->memory->pcb->lineCounter, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->memory->pcb->quantum - aux->memory->pcb->lineCounter, "");
            aux = aux->next;
        }
    }
}

void renderPriority(ScheduleList *scheduleList, int maxElements) {
    Schedule *aux = scheduleList->start;
    int count = 0;

    printf("PR: ");
    if(maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->memory->pcb->priority, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->memory->pcb->priority, "");
            aux = aux->next;
        }
    }
}

void renderScheduleList(ScheduleList *scheduleList, int maxElements) {

    if (scheduleList->start == NULL)
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

void renderListFinished(ScheduleList *list, int maxElements) {
    if (list->start == NULL)
        printf("Empty list!\n");
    else {
        renderId(list, maxElements);
        printf("\n");
        renderProcessingTime(list, maxElements);
        printf("\n");
        renderInitialQuantum(list, maxElements);
        printf("\n");
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void renderScreen(ScheduleList* jobs, ScheduleList* ready, ScheduleList* blocked, ScheduleList* finished, ScheduleList* cpu, unsigned int clock,
                  unsigned int time, char* action) {
    // Clear screen.
    clearScreen();

    // Printing lists.
    printf("Jobs:       \n");
    renderScheduleList(jobs, -1);
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
    printf("\n\nProcessing:");
    renderElement(cpu->start);
    printf("\n\nAction: %s\n", action);
    printf("----------------------------------------\n");
}
