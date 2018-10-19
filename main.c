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
    printf("\nProcess: %d", cpu->start->id);
    printf("\nAction: %s", action);
    printf("---------------------");
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
        return moveBetweenLists(cpu, finished);
    } else if (status == 2) { // Process blocked.
        // Get wait time for the pcb i/o interruption and move to blocked.
        (*cpu)->start = getWaitTime((*cpu)->start);
        return moveBetweenLists(cpu, blocked);
    }

    return false;
}

// Manage the blocked list and return an action status;
int manageBlocked(List** ready, List** blocked, bool action) {
    // Decrement wait time
    PCB *aux = (*blocked)->start;
    while (aux != NULL) {
        if (aux->waitTime > 0) aux->waitTime--;

        // When the wait ends, moves to ready. If not superior action occurs.
        if (aux->waitTime == 0 && !action) {
            return moveElementBetweenLists(blocked, ready, aux->id);
        }

        aux = aux->next;
    }
    return false;
}

int manageJobs(List** ready, List** blocked, List** jobs, unsigned int* processToLoad, bool action) {
    // When ready list allow new data, move it. If not superior action occurs.
    if ( listCounter((*ready)) + listCounter((*blocked)) <= maxReadyLength && !action) {
        return moveBetweenLists(jobs, ready);
    }

    // When have process to load, generate then.  If not superior action occurs.
    if ((*processToLoad) > 0 && !action) {
        (*processToLoad)--;
        *jobs = listInsertSorted(*jobs, generatePCB(id++, clockTime));
        return true;
    }

    return false;
}


void runClock(List** cpu, List** ready, List** blocked, List** jobs, List** finished,  unsigned int* processToLoad) {
    bool action;

    printf("----------cpu-----------");

    // Execute the CPU manager
    action = manageCPU(cpu, ready, blocked, finished);

    printf("----------blocked-----------");

    // After cpu manage the blocked queue
    action = manageBlocked(ready, blocked, action);

    printf("----------jobs-----------");

    // For last, manage the jobs queue.
    manageJobs(ready, blocked, jobs, processToLoad, action);
}

int main(int argc, const char *argv[]) {
    printf("---------------------");

    // Lists
    List *jobs = newList();
    List *ready = newList();
    List *cpu = newList();
    List *blocked = newList();
    List *finished = newList();

    printf("---------------------");

    // Variables
    char exec = 'y';
    bool status = true;
    unsigned int processInDisk = 10;

    // Generate initial data
//    for (unsigned int i = 0; i < 19; ++i) {
//        jobs = listInsertSorted(jobs, generatePCB(id++, clockTime));
//        clockTime++;
//    }

    printf("---------------------");

    // Control Flux
    while (status) {
        // Render the screen.
        printf("---------------------");
        renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockTime, "teste");
        printf("---------------------");
//        runClock(&cpu, &ready, &blocked, &jobs, &finished, &processInDisk);

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
