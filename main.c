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
#include "libs/list.h"
#include "libs/pcb.h"
#include "time.h"

unsigned int id = 1;
unsigned int clock = 1;
#define quantum 35

int main(int argc, const char * argv[]) {

    // Generate Random Numbers
    srand((unsigned int)time(NULL));

    // Lists
    List *jobs = newList();
    List *ready = newList();
    List *blocked = newList();
    List *finished = newList();

    // Variables
    int exec = 1;
    int i;


    // Generate initial data
    for(int i = 0; i < 10; ++i) {
        listInsertSorted(jobs, newPCB(&id), clock);
        clock++;
    }


    // Control Flux
    while(exec) {

        // One process is created every 20 clocks
        // Update priority of processes every 20 clocks
        if(clock%20 == 0) {
            listInsertSorted(jobs, newPCB(&id), clock);
            listUpdatePriority(jobs, clock);
        }

        foo();

        clock++;
        exec = 0;
    }

    return 0;

}
