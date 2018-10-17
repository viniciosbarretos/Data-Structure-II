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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libs/list.h"
#include "libs/pcb.h"

unsigned int id = 1;
unsigned int clock = 1;
#define processorQuantum 35

int main(int argc, const char * argv[]) {

    // Generate Random Numbers
    srand((unsigned int)time(NULL));

    // Lists
    List *jobs = newList();
    List *ready = newList();
    List *blocked = newList();
    List *finished = newList();

    // Variables
    char exec = 'y';
    unsigned int i;


    // Generate initial data
    for(int i = 0; i < 10; ++i) {
        listInsertSorted(jobs, newPCB(&id), clock);
        clock++;
    }


    // Control Flux
    while(exec=='y') {

        // One process is created every 20 clocks
        // Update priority of processes every 20 clocks
        if(clock%20 == 0) {
            listInsertSorted(jobs, newPCB(&id), clock);
            listUpdatePriority(jobs, clock); // This cannot happen every clock due optimization
        }

        /*
         * Insert process(es) at Ready List
         * Send process to execution
         *      Checks Interruption
         *          y -> Send to Block List
         *          n -> Send to Ready or finished
         * Show to user
         */


        clock++;

        printf("Do you want to stop? (y/n):  ");
        scanf("%c", exec);
    }

    return 0;

}
