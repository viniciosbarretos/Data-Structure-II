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
#define _status int
#define maxReadyLength 20

// Execution statuses
#define _statusNone             0
#define _statusMoveReadyCPU     1
#define _statusMoveCPUReady     2
#define _statusMoveCPUBlocked   3
#define _statusMoveCPUFinish    4
#define _statusMoveBlockedReady 5
#define _statusMoveJobsReady    6
#define _statusCreatePCB        7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/list.h"
#include "libs/pcb.h"
#include "libs/render.h"

unsigned int id = 1;
unsigned int clockTime = 0;
unsigned int clockPast = 0;
unsigned int remainingQuantum = processorQuantum;
unsigned int lastId = 0;

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
_status manageCPU(List** cpu, List** ready, List** blocked, List** finished) {

    // When CPU empty, get next process.
    if ((*cpu)->start == NULL) {
        // Set max quantum.
        remainingQuantum = processorQuantum;

        // Move to cpu.
        if (moveBetweenLists(ready, cpu)) {
            // Change the status.
            ((*cpu)->start)->status = _pcbStatusRunning;
            return _statusMoveReadyCPU;
        } else {
            return _statusNone;
        }
    }

    // Set the start time, if needed.
    if (((*cpu)->start)->startProcessingTime == 0) { // First execution.
        ((*cpu)->start)->startProcessingTime = clockTime;
    }

    // Execute next instruction.
    unsigned int status = executeCPU((*cpu)->start);
    remainingQuantum--;

    // Check for a exceeded quantum.
    if (remainingQuantum == 0) {
        // Update status.
        ((*cpu)->start)->status = _pcbStatusReady;

        moveBetweenLists(cpu, ready);
        return _statusMoveCPUReady;
    }

    // Manage the process if necessary.
    if (status == 0) { // Process finished.
        // Set end time.
        ((*cpu)->start)->endProcessingTime = clockTime;

        // Change status
        ((*cpu)->start)->status = _pcbStatusDone;

        // Move pcb to finished.
        if (moveBetweenLists(cpu, finished)) return _statusMoveCPUFinish;
    } else if (status == 2) { // Process blocked.
        // Get wait time for the pcb i/o interruption and move to blocked.
        (*cpu)->start = getWaitTime((*cpu)->start);

        // Change status
        ((*cpu)->start)->status = _pcbStatusBlocked;

        if (moveBetweenLists(cpu, blocked)) return _statusMoveCPUBlocked;
    }

    return _statusNone;
}

// Manage the blocked list and return an action status;
_status manageBlocked(List** ready, List** blocked) {
    // Decrement wait time
    PCB *aux = (*blocked)->start;
    while (aux != NULL) {
        if (aux->waitTime > 0) aux->waitTime--;

        // When the wait ends, moves to ready. If not superior action occurs.
        if (aux->waitTime == 0) {
            // Change status
            aux->status = _pcbStatusReady;

            if (moveElementBetweenLists(blocked, ready, aux->id)) return _statusMoveBlockedReady;
        }

        aux = aux->next;
    }
    return _statusNone;
}

_status manageJobs(List** ready, List** blocked, List** jobs, unsigned int* processToLoad) {
    // When ready list allow new data, move it. If not superior action occurs.
    if ( listCounter((*ready)) + listCounter((*blocked)) <= maxReadyLength) {
        // Change status
        if ((*jobs)->end != NULL) {
            ((*jobs)->end)->status =  _pcbStatusReady;
        }

        if (moveBetweenLists(jobs, ready)) return _statusMoveJobsReady;
    }

    // When have process to load, generate then.  If not superior action occurs.
    if ((*processToLoad) > 0) {
        (*processToLoad)--;
        *jobs = listInsertSorted(*jobs, generatePCB(id++, clockTime));
        return _statusCreatePCB;
    }

    return _statusNone;
}


int runClock(List** cpu, List** ready, List** blocked, List** jobs, List** finished,  unsigned int* processToLoad) {
    int action = _statusNone;
    clockPast = 0;

    while (action == _statusNone) {
        // Execute the CPU manager.
        action = manageCPU(cpu, ready, blocked, finished);

        // After cpu manage the blocked queue, if not occur any action before.
        if (action == _statusNone)
            action = manageBlocked(ready, blocked);

        // For last, manage the jobs queue.
        if (action == _statusNone)
            action = manageJobs(ready, blocked, jobs, processToLoad);

        // One process is created every 20 clocks
        // Update priority of processes every 20 clocks
        if (clockTime % 20 == 0) {
            (*processToLoad)++;
        }

        // Increment clock.
        clockTime++;
        clockPast++;
    }

    return action;
}

int main(int argc, const char *argv[]) {
    // Lists
    List *jobs = newList();
    List *ready = newList();
    List *cpu = newList();
    List *blocked = newList();
    List *finished = newList();

    // Variables
    _status status;

    // Start simulation with 10 process to load.
    unsigned int processInDisk = 10;

    // Initial render.
    renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockTime, "Simulation started");
    printf("\nEnter to next step: ");
    status = (getchar() != 'e') ? true: false;
    getchar();

    // Control Flux
    while (status) {
        // Run a clock iteration.
        status = runClock(&cpu, &ready, &blocked, &jobs, &finished, &processInDisk);

        // Render screen
        renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockPast, getStatus(status, lastId));

        // Print control information.
        printf("\nEnter to next step: ");
        status = (getchar() != 'e') ? true: false;
        getchar();
    }

    return 0;
}
