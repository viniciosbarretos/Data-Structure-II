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

// Simulation defaults.
#define processorQuantum 45
#define maxReadySize 10
#define initialProcessQuantity 10
#define generationProcessTime 40

// General definitions.
#define true 1
#define false 0
#define _action int

// Execution status
#define _actionNone             0
#define _actionMoveReadyCPU     1
#define _actionMoveCPUReady     2
#define _actionMoveCPUBlocked   3
#define _actionMoveCPUFinish    4
#define _actionMoveBlockedReady 5
#define _actionMoveJobsReady    6
#define _actionCreatePCB        7

// CPU status
#define _processFinished 0
#define _processRunning  1
#define _processBlocked  2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libs/list.h"
#include "libs/pcb.h"
#include "libs/render.h"

unsigned int id = 1;
unsigned int clockTime = 0;
unsigned int clockPast = 0;
unsigned int remainingQuantum;
unsigned int processToLoad;
unsigned int lastId = 0;

unsigned int executeCPU(PCB* pcb) {
    // Increment line counter.
    pcb->lineCounter++;

    // Return the cpu status of this process. (0 -> finished; 1 -> running; 2 -> Blocked).
    if (pcb->lineCounter == pcb->interruption) {
        return _processBlocked; // Blocked.
    } else if (pcb->lineCounter == pcb->quantum) {
        return _processFinished; // Finished.
    } else {
        return _processRunning; // Running.
    }
}


// Manage the PCB iteration around cpu and return an action status;
_action manageCPU(List** cpu, List** ready, List** blocked, List** finished) {

    // When CPU empty, get next process.
    if (isEmpty(cpu)) {

        // If ready isn't empty.
        if (!isEmpty(ready)) {
            // Move pcb to cpu.
            moveBetweenLists(ready, cpu, _pcbStatusRunning);

            // Set max quantum.
            remainingQuantum = processorQuantum;

            // Get the process id for the action.
            lastId = ((*cpu)->start)->id;

            // Set the start time, if it's first execution.
            if (((*cpu)->start)->startProcessingTime == 0) {
                ((*cpu)->start)->startProcessingTime = clockTime;
            }

            return _actionMoveReadyCPU;
        }
    } else {
        // Execute the next instruction.
        unsigned int status = executeCPU((*cpu)->start);
        remainingQuantum--;

        // Manage the process if necessary.
        if (status == _processFinished) { // Process finished.
            // Set end time.
            ((*cpu)->start)->endProcessingTime = clockTime;

            // Get the process id for the action.
            lastId = ((*cpu)->start)->id;

            // Move pcb to finished.
            moveBetweenLists(cpu, finished, _pcbStatusDone);
            return _actionMoveCPUFinish;

        } else if (status == _processBlocked) { // Process blocked.
            // Get wait time for the pcb i/o interruption and move to blocked.
            (*cpu)->start = getWaitTime((*cpu)->start);

            // Get the process id for the action.
            lastId = ((*cpu)->start)->id;

            // Move pcb to blocked.
            moveBetweenLists(cpu, blocked, _pcbStatusBlocked);
            return _actionMoveCPUBlocked;

        } else if (remainingQuantum == 0) { // Check for a exceeded quantum.
            // Get the process id for the action.
            lastId = ((*cpu)->start)->id;

            // Move pcb to ready.
            moveBetweenLists(cpu, ready, _pcbStatusReady);
            return _actionMoveCPUReady;
        }
    }

    return _actionNone;
}

// Manage the blocked list and return an action status;
_action manageBlocked(List** ready, List** blocked) {
    // iterate for each process in blocked queue.
    PCB *aux = (*blocked)->start;
    while (aux != NULL) {
        // Decrement wait time
        if (aux->waitTime > 0) aux->waitTime--;

        // When the wait ends, moves to ready. If not superior action occurs.
        if (aux->waitTime == 0) {
            // Get the process id for the action.
            lastId = aux->id;

            // Move pcb to ready.
            moveElementBetweenLists(blocked, ready, aux->id, _pcbStatusReady);
            return _actionMoveBlockedReady;
        }

        // Increment aux.
        aux = aux->next;
    }

    return _actionNone;
}

_action manageJobs(List** ready, List** blocked, List** jobs) {
    // When ready list allow new data, move it. If not superior action occurs.
    if ( listCounter((*ready)) + listCounter((*blocked)) < maxReadySize && !isEmpty(jobs)) {

        // Get the process id for the action.
        lastId = ((*jobs)->end)->id;

        // Move pcb to ready.
        moveBetweenLists(jobs, ready, _pcbStatusReady);
        return _actionMoveJobsReady;
    }

    // When have process to load, generate then.  If not superior action occurs.
    if (processToLoad > 0) {
        processToLoad--;

        // Create the new pcb.
        PCB *newProcess = generatePCB(id++, clockTime);

        // Get the process id for the action.
        lastId = newProcess->id;

        // Insert element in jobs.
        *jobs = listInsertSorted(*jobs, newProcess);

        return _actionCreatePCB;
    }

    return _actionNone;
}


_action runClock(List** cpu, List** ready, List** blocked, List** jobs, List** finished) {
    int action = _actionNone;
    clockPast = 0;

    while (action == _actionNone) {
        // Execute the CPU manager.
        action = manageCPU(cpu, ready, blocked, finished);

        // After cpu, manage the blocked queue, if doesn't occur any action before.
        if (action == _actionNone)
            action = manageBlocked(ready, blocked);

        // For last, manage the jobs queue.
        if (action == _actionNone)
            action = manageJobs(ready, blocked, jobs);

        // One process is created every processDividerMod (40) clocks.
        if (clockTime % generationProcessTime == 0) {
            processToLoad++;
            // Update priority for old elements.
            *jobs = listUpdatePriority(*jobs, clockTime);
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

    // srand initialization.
    srand((unsigned int)time(NULL));

    // Variables
    _action action;
    int shell;

    // Start simulation with 10 process to load.
    processToLoad = initialProcessQuantity;

    // Initial render.
    renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockPast, "Simulation started");
    printf("\nPress Enter to the next step: ");
    shell = (getchar() != 'e') ? true : false;
    getchar();

    // Control Flux
    while (shell) {
        // Run a clock iteration while doesn't occur an action.
        action = runClock(&cpu, &ready, &blocked, &jobs, &finished);

        // Render screen.
        renderScreen(jobs, ready, blocked, finished, cpu, clockTime, clockPast, getStatus(action, lastId));

        // Print control information.
        printf("\nEnter to next step: ");
        shell = (getchar() != 'e') ? true: false;
        getchar();
    }

    return 0;
}