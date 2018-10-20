#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "list.h"

void renderElement(PCB *pcb) {
    if (pcb != NULL) {
        printf("[%d: %d]", pcb->id, pcb->quantum);
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