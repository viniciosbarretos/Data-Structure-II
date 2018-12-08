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

    int operator;

    //Costumer features:
    unsigned accountNumber;
    char name[40];
    char customerType;
    unsigned overbalance;
    //---------------------

    //clearScreen();
    printf("\n1 - Register Customer\n");
    printf("2 - Remove Customer\n");
    printf("3 - Search Customer by Acc number\n");
    printf("4 - Show Hash Table\n");
    printf("0 - End Simulation\n");

    printf("\nSelect your option: ");

    switch(operator) {
        case 1:
            //clearScreen();
            printf("Account number: ");
            scanf("%d", &accountNumber);

            printf("Name: ");
            scanf("%[^\n]", name);

            registerCostumer(accountNumber, name, customerType, overbalance);
            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;

        case 0:

            system("exit");
            break;
    }
}
int main() {
    unsigned option;

    do {
        printOptions();
        scanf("%d", &option);
        cleanBuffer();
        switch (option) {
            case 0:
                break;
            case 1:
                registerCustomer();
                break;
            case 2:
                //check if is empty
                removeCustomer();
                break;
            case 3:
                //check if is empty
                searchCustomer();
                break;
            case 4:
                //check if is empty
                showHashTable();
                break;
            default:
                printf("\nInvalid Option! Try again.");

        }

    } while (option);



    return 0;
}