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

typedef struct pcb {
    struct pcb *next;
    unsigned int id;
    unsigned int quantum;
    unsigned short int priority;
    unsigned short int state;
    unsigned int interruption;
} pcb;

int main(int argc, const char * argv[]) {
    
    int v =0;
    
    return 0;
}
