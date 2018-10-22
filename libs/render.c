#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "list.h"

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
        case 0:
            sprintf(str, "Nothing happens");
            break;

        case 1:
            sprintf(str, "Process %d dispatched", id);
            break;

        case 2:
            sprintf(str, "Process %d interrupted", id);
            break;

        case 3:
            sprintf(str, "Process %d I/O wait", id);
            break;

        case 4:
            sprintf(str, "Process %d exited", id);
            break;

        case 5:
            sprintf(str, "Process %d I/O completed", id);
            break;

        case 6:
            sprintf(str, "Process %d admitted", id);
            break;

        case 7:
            sprintf(str, "Process %d created", id);
            break;

        default:
            sprintf(str, "I do not know");
    }

    return str;
}


void renderElement(PCB *pcb) {
    if (pcb != NULL) {
        printf(" ID: [%4d%1s]\n", pcb->id, "");
        printf("%12sQU: [%4d%1s] ", "", pcb->quantum - pcb->lineCounter, "");
    }
}

void renderId(List *list, int maxElements) {
    PCB *aux = list->start;
    int count = 0;

    printf("ID: ");
    if(maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->id, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->id, "");
            aux = aux->next;
        }
    }
}

void renderQuantum(List *list, int maxElements) {
    PCB *aux = list->start;
    int count = 0;

    printf("QU: ");
    if (maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->quantum - aux->lineCounter, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->quantum - aux->lineCounter, "");
            aux = aux->next;
        }
    }
}

void renderPriority(List *list, int maxElements) {
    PCB *aux = list->start;
    int count = 0;

    printf("PR: ");
    if(maxElements != -1) {
        while (aux != NULL && count < maxElements) {
            printf("[%4d%1s] ", aux->priority, "");
            aux = aux->next;
            count++;
        }
    } else {
        while (aux != NULL) {
            printf("[%4d%1s] ", aux->priority, "");
            aux = aux->next;
        }
    }
}

void renderList(List *list, int maxElements) {

    if (list->start == NULL)
        printf("Empty list!\n");
    else {
        renderId(list, maxElements);
        printf("\n");
        renderPriority(list, maxElements);
        printf("\n");
        renderQuantum(list, maxElements);
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

void renderScreen(List* jobs, List* ready, List* blocked, List* finished, List* cpu, unsigned int clock,
                  unsigned int time, char* action) {
    // Clear screen.
    clearScreen();

    // Printing lists.
    printf("Jobs:       \n");
    renderList(jobs, -1);
    printf("\nReady:    \n");
    renderList(ready, -1);
    printf("\nBlocked:  \n");
    renderList(blocked, -1);
    printf("\nFinished: \n");
    renderList(finished, 12);

    // Printing the additional data.
    printf("\n----------------------------------------");
    printf("\nClock: %d", (int) clock);
    printf("\t\t\tElapsed Clock: %d", (int) time);
    printf("\n\nProcessing:");
    renderElement(cpu->start);
    printf("\n\nAction: %s\n", action);
    printf("----------------------------------------\n");
}
