#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/customer.h"
#include "libs/hashing.h"
#include "libs/render.h"
#include "math.h"


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

//    switch(operator) {
//        case 1:
//            //clearScreen();
//            printf("Account number: ");
//            scanf("%d", &accountNumber);
//
//            printf("Name: ");
//            scanf("%[^\n]", name);
//
////            registerCostumer(accountNumber, name, customerType, overbalance);
//            break;
//
//        case 2:
//
//            break;
//
//        case 3:
//
//            break;
//
//        case 4:
//
//            break;
//
//        case 0:
//
//            system("exit");
//            break;
//    }
}

void render(Dir *dir) {
    int n = (int) pow(2, dir->globalDepth);
    int i, j;

    printf("Directory\n");
    for (i=0; i<n; i++) {
        if (dir->key[i]) {
            printf("{");
            for (j=0; j<4; j++) {
                printf("%d|", dir->key[i]->items[j].id);

            }
            printf("}");

        } else {
            printf(" NULL ");
        }

    }
}

int main() {
    // Create the directory
    Dir *dir = newDirectory();
    int id = 0;

    Customer customer = {0, "teste", "o", 21.5, };
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;

    render(dir);
    printf("\n");
    printf("\n");

    renderHashTable(dir);

    printf("\n");
    printf("\n");

    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    id++;
    insertOnDir(dir, &id, customer);
    render(dir);
    printf("\n");
    printf("\n");

    renderHashTable(dir);

    printf("\n");
    printf("\n");
    removeFromDir(dir, 4);
    removeFromDir(dir, 12);
    removeFromDir(dir, 16);
    render(dir);



    unsigned option;

    do {
        printOptions();
        scanf("%d", &option);
        cleanBuffer();
        switch (option) {
            case 0:
                printf("\n\nBye bye :)\n");
                break;
            case 1:
                registerCustomer(id);
                id++;
                break;
            case 2:
                //check if is empty
                if(isEmpty(dir))
                    removeCustomer(id);
                else
                    printf("\nNo registered clients!\n");
                break;
            case 3:
                //check if is empty
                if(isEmpty(dir))
                    searchCustomer(14);
                else
                    printf("\nNo registered clients!\n");
                break;
            case 4:
                //check if is empty
                if(isEmpty(dir))
                    renderHashTable(dir);
                else
                    printf("\nNo registered clients!\n");
                break;
            default:
                printf("\nInvalid Option! Try again.");

        }

    } while (option);



    return 0;
}