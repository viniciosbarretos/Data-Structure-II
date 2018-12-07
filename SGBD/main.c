#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/customer.h"
#include "libs/render.h"


// Clean buffer after a text input
void cleanBuffer() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}

//Menu options
void printOptions() {
    //clearScreen();
    printf("\n1 - Register Customer\n");
    printf("2 - Remove Customer\n");
    printf("3 - Search Customer by Acc number\n");
    printf("4 - Show Hash Table\n");
    printf("0 - End Simulation\n");

    printf("\nSelect your option: ");
}
int main() {

    printOptions();

    return 0;
}