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

char* getStatus(int status) {
    char *str = (char*) malloc(sizeof(char) * 64);

    switch (status) {
        case 0:
            str = strCopy(str, "Nothing happens");
            break;

        case 1:
            str = strCopy(str, "Process moved from Ready  to CPU");
            break;

        case 2:
            str = strCopy(str, "Process moved from CPU to Ready");
            break;

        case 3:
            str = strCopy(str, "Process moved from CPU to Blocked");
            break;

        case 4:
            str = strCopy(str, "Process moved from CPU to Finished");
            break;

        case 5:
            str = strCopy(str, "Process moved from Blocked to Ready");
            break;

        case 6:
            str = strCopy(str, "Process moved from Jobs to Ready");
            break;

        case 7:
            str = strCopy(str, "Process created");
            break;

        default:
            str = strCopy(str, "I don't know");
    }

    return str;
}


void renderElement(PCB *pcb) {
    if (pcb != NULL) {
        printf("[%d: %d]", pcb->id, pcb->quantum - pcb->lineCounter);
    }
}

void renderList(List *list) {
    PCB *aux = list->start;

    if (aux == NULL) {
        printf("! Empty list !");
    }

    while (aux != NULL) {
        renderElement(aux);
        aux = aux->next;
    }
}

void renderScreen(List* jobs, List* ready, List* blocked, List* finished, List* cpu, unsigned int clock,
                  unsigned int time, char* action) {
    printf("Jobs:       ");
    renderList(jobs);
    printf("\nReady:    ");
    renderList(ready);
    printf("\nBlocked:  ");
    renderList(blocked);
    printf("\nFinished: ");
    renderList(finished);
    printf("\n\nClock: %d", (int) clock);
    printf("\tClock past: %d", (int) time);
    printf("\nProcess:");
    renderElement(cpu->start);
    printf("\nAction: %s", action);
}