//
//  Laboratory of Data Structure II
//  Vinicios Barretos
//  Vinicius Martins
//  David Candelero
//  Thiago Leal
//

/* Status
 0 -> New
 1 -> Ready
 2 -> In execution
 3 -> Blocked
 4 -> Done
 */

#include <stdio.h>
#include <stdlib.h>
#include "libs/list.h"
#include "libs/pcb.h"

//inserting process(es)
List * insertProcess(List *list, int quantum) {
    PCB *pcb = newPcb();
    pcb->quantum = (unsigned) quantum;
    list = listInsert(list, pcb);

    return list;
}

//list print function
void printQueue(PCB *queue) {
    if (queue == NULL)
        printf("Lista Vazia!");
    else {
        if (queue->next != NULL) {
            printQueue(queue->next);
            printf(" |%d|", queue->quantum);
        }
        else
            printf(" |%d|", queue->quantum);
    }
}


//scheduling algorithm
PCB *RoundRobin(List *list) {
    PCB *queue = list->front;
    PCB *aux = queue;
    if(queue != NULL) {
        if(aux->quantum <= 35) {
            //If we need to show the time (quantum) elapsed.
            aux->quantum = 0;
            queue = queue->next;
            return queue;
            //insert in the finishedQueue (we'll probably need an id for each process)
            //insertProcess(queue, id);
        } else
            aux->quantum = aux->quantum - 35;

        //removing from the first position and placing in the last (after removing the processed quantum)
        if(queue->next!= NULL) {
            queue = queue->next;
            queue = insertProcess(queue, aux->quantum);
        }
        return queue;
    }

    return NULL;
}

//print function for all queues
void printStatus(PCB *jobsQueue, PCB *readyQueue, PCB *finishedQueue) {
    printf("\n");
    int i;

    for(i = 0; i < 50; i++)
        printf("-");

    printf("\n");
    printf("JobsQueue:  ");
    printQueue(jobsQueue);
    printf("\n");
    printf("ReadyQueue:  ");
    printQueue(readyQueue);
    printf("\n");
    printf("FinishedQueue:  ");
    printQueue(finishedQueue);
    printf("\n");
    for(i = 0; i < 50; i++)
        printf("-");

    printf("\n");
}

int main(int argc, const char * argv[]) {
    List *jobsQueue, *readyQueue, *blockedqueue, *finishedQueue;
    int quantum, x = 0;
    char choice, choice2;

    do {
        printf("Digite 1 para inserir novo processo, 2 para continuar e 0 para finalizar.");
        scanf("%d", &x);

        //printf ("Deseja criar um novo processo?\n[y/n]:");
        //scanf(" %c", &choice);
        if (x == 1) {
                printf("Digite o quantum do processo:");
                scanf("%d", &quantum);
                jobsQueue = insertProcess(jobsQueue, quantum);
                printStatus(jobsQueue,readyQueue, finishedQueue);

                printf("Deseja inseri-lo na lista de prontos?\n[y/n]:");
                scanf(" %c", &choice2);
                if (choice2 == 'y') {
                    readyQueue = insertProcess(readyQueue, quantum);
                    printStatus(jobsQueue,readyQueue, finishedQueue);
                }
            readyQueue = RoundRobin(readyQueue);
            printStatus(jobsQueue,readyQueue, finishedQueue);
        } else {
            if (x == 2) {
                readyQueue = RoundRobin(readyQueue);
                printStatus(jobsQueue, readyQueue, finishedQueue);
            }
        }

    } while (x != 0);

    return 0;
}
