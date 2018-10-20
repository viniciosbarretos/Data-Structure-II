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

/* Priority
 0 -> Low
 1 -> Medium
 2 -> High
 */

#define processorQuantum 35
#define true 1
#define false 0
#define bool int
#define maxReadyLength 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/list.h"
#include "libs/pcb.h"
#include "libs/render.h"

unsigned int id = 1;
unsigned int clockTime = 0;

//char **actions = {{"ij", "Inserted on Jobs"}, {"mr", "Moved to Ready"}};

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


unsigned int executeCPU(PCB* pcb) {
    // Increment line counter.
    pcb->lineCounter++;

    // Return the cpu status of this process. (0 -> finished; 1 -> running; 2 -> Blocked).
    if (pcb->lineCounter == pcb->interruption) {
        return 2; // Blocked.
    } else if (pcb->lineCounter == pcb->quantum) {
        return 0; // Finished.
    } else {
        return 1; // Running.
    }
}


// Manage the PCB iteration around cpu and return an action status;
int manageCPU(List** cpu, List** ready, List** blocked, List** finished) {

    // When CPU empty, get next process.
    if ((*cpu)->start == NULL) {
        return moveBetweenLists(ready, cpu);
    }

    // Execute next instruction.
    unsigned int status = executeCPU((*cpu)->start);

    // Manage the process if necessary.
    if (status == 0) { // Process finished.
        // Mode pcb to finished.
        if (moveBetweenLists(cpu, finished)) return true;
    } else if (status == 2) { // Process blocked.
        // Get wait time for the pcb i/o interruption and move to blocked.
        (*cpu)->start = getWaitTime((*cpu)->start);
        if (moveBetweenLists(cpu, blocked)) return true;
    }

    return false;
}

// Manage the blocked list and return an action status;
int manageBlocked(List** ready, List** blocked) {
    // Decrement wait time
    PCB *aux = (*blocked)->start;
    while (aux != NULL) {
        if (aux->waitTime > 0) aux->waitTime--;

        // When the wait ends, moves to ready. If not superior action occurs.
        if (aux->waitTime == 0) {
            if (moveElementBetweenLists(blocked, ready, aux->id)) return true;
        }

        aux = aux->next;
    }
    return false;
}

int manageJobs(List** ready, List** blocked, List** jobs, unsigned int* processToLoad) {
    // When ready list allow new data, move it. If not superior action occurs.
    if ( listCounter((*ready)) + listCounter((*blocked)) <= maxReadyLength) {
        if (moveBetweenLists(jobs, ready)) return true;
    }

    // When have process to load, generate then.  If not superior action occurs.
    if ((*processToLoad) > 0) {
        (*processToLoad)--;
        *jobs = listInsertSorted(*jobs, generatePCB(id++, clockTime));
        return true;
    }

    return false;
}


void runClock(List** cpu, List** ready, List** blocked, List** jobs, List** finished,  unsigned int* processToLoad) {
    int action;

    // Execute the CPU manager
    action = manageCPU(cpu, ready, blocked, finished);

    // After cpu manage the blocked queue, if not occur any action before
    if (!action)
        action = manageBlocked(ready, blocked);

    // For last, manage the jobs queue.
    if (!action)
        manageJobs(ready, blocked, jobs, processToLoad);
}

int main(int argc, const char *argv[]) {

    // Lists
    List *jobs = newList();
    List *ready = newList();
    List *cpu = newList();
    List *blocked = newList();
    List *finished = newList();

    // Variables
    char exec = 'y';
    bool status = true;
    unsigned int processInDisk = 10;

    // Initial render.
    renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockTime, "teste");
    printf("\nEnter to next step: ");
    status = (getchar() != 'e') ? true: false;

    // Generate initial data
//    for (unsigned int i = 0; i < 19; ++i) {
//        jobs = listInsertSorted(jobs, generatePCB(id++, clockTime));
//        clockTime++;
//    }

    // Control Flux
    while (status) {
        // Render the screen.

//        if (clockTime < 1) {
//            jobs = listInsertSorted(jobs, generatePCB(id++, clockTime));
//        }

//        if (clockTime > 1) {
//            moveBetweenLists(&jobs, &ready);
//            renderElement(jobs->start);
//        }

//        if (clockTime % 2 == 1) {
//            printf("-3-");
//            moveBetweenLists(&ready, &finished);
//        }

//        printf("---------------%d---------------", clockTime);

        printf("-----------------------------------------------------------------------\n");
        runClock(&cpu, &ready, &blocked, &jobs, &finished, &processInDisk);
        renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockTime, "teste");

        // One process is created every 20 clocks
        // Update priority of processes every 20 clocks
//        if(clockTime%20 == 0) {
//            listInsertSorted(jobs, generatePCB(&id), clockTime);
//            listUpdatePriority(jobs, clockTime); // This cannot happen every clockTime due optimization
//        }

        /*
         * Insert process(es) at Ready List
         * Send process to execution
         *      Checks Interruption
         *          y -> Send to Block List
         *          n -> Send to Ready or finished
         * Show to user
         */


        clockTime++;

        printf("\nEnter to next step: ");
//        exec = getchar();
//        scanf("%c", &exec);
        status = (getchar() != 'e') ? true: false;

    }

    return 0;

}
