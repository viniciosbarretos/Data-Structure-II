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
        printf("[%d: %d]", pcb->id, pcb->quantum - pcb->lineCounter);
    }
}

void renderInfo(int n) {
    printf("[%*d%*s]", 4, n, 1, "");
}

void renderId(List *list) {
    PCB *aux = list->start;

    while (aux != NULL) {
        renderInfo(aux->id);
        aux = aux->next;
    }
}

void renderQuantum(List *list) {
    PCB *aux = list->start;

    while (aux != NULL) {
        renderInfo(aux->quantum - aux->lineCounter);
        aux = aux->next;
    }
}

void renderList(List *list) {

    if (list->start == NULL)
        printf("Empty list!\n");
    else {
        renderId(list);
        printf("\n");
        renderQuantum(list);
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
    renderList(jobs);
    printf("\nReady:    \n");
    renderList(ready);
    printf("\nBlocked:  \n");
    renderList(blocked);
    printf("\nFinished: \n");
    renderList(finished);

    // Printing the additional data.
    printf("\n\nClock: %d", (int) clock);
    printf("\tClock past: %d", (int) time);
    printf("\nProcess:");
    renderElement(cpu->start);
    printf("\nAction: %s\n", action);
}
