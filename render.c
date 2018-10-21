#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "list.h"
#include "render.h"


void renderElement(PCB *pcb) {
    if (pcb != NULL) {

        printf("\n\t[%d]\t\n[%d]", pcb->id, pcb->quantum);
    }
}

void renderId(List *list) {
    PCB *aux = list->start;

    if (aux == NULL) {
        if (aux->next != NULL) {
            list->start = aux->next;
            renderId(list);
            printf("%d\t", aux->id);
        } else
            printf("%d\t", aux->id);
    }
}

void renderQuantum(List *list) {
    PCB *aux = list->start;

    if (aux != NULL) {
        if (aux->next != NULL) {
            list->start = aux->next;
            renderQuantum(list);
            printf("%d\t", aux->quantum);
        } else
            printf("%d\t", aux->quantum);
    }
}

void renderList(List *list) {

    if (list == NULL)
        printf("Empty list!\n");
    else {
        renderId(list);
        printf("\n");
        renderQuantum(list);
        printf("\n");
    }

    //PCB *aux = list->start;

    /*
    if (aux == NULL) {
        printf("! Empty list !");
    }

    while (aux != NULL) {
        renderElement(aux);
        aux = aux->next;
    }
     */
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