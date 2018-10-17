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
#include "time.h"

int id = 1;

void printProcessInfo(PCB *queue) {
    while(queue != NULL) {
        printf("ID: %d\t\t Quant: %d\t\t Pri: %d\t\tStat: %d\t\t Interr: %d\t\tWT: %d\n", queue->id, queue->quantum, queue->priority, queue->status, queue->interruption, queue->waitTime);
        queue = queue->next;
    }
}

int main(int argc, const char * argv[]) {

    srand((int)time(NULL));

    int i;
    /*
    List *jobsQueue = newList();
    List *readyQueue = newList();
    List *blockedqueue = newList();
    List *finishedQueue = newList();
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

     */

    List *jobs = newList();
    PCB *aux;

    for(i=0; i<20; i++) {
        listInsertSorted(jobs, newPCB(&id));
    }

    printProcessInfo(jobs->start);

    printf("\n\nstart %d | end %d \n\n\n", jobs->start->id, jobs->end->id);

    for(i=0; i<5; i++) {
        for (aux = jobs->start; aux != NULL; aux = aux->next) {
            if (rand() % 2)
                aux->waitTime += (int) aux->quantum / 2;
        }
    }

    listUpdatePriority(jobs);


    printProcessInfo(jobs->start);

    printf("\n\nstart %d | end %d ", jobs->start->id, jobs->end->id);


    return 0;
}
