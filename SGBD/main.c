#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h"
#include "libs/customer.h"
#include "libs/hashing.h"
#include "libs/render.h"
#include "libs/utils.h"

Customer newCostumer() {
    Customer c;

    // The costumer information.
    printf("\nAccount Number:");
    scanf("%d ", &c.id);

    printf("\nName:");
    scanf("%s ", c.name);

    //Validating customer type.
    do {
        printf("\nType('P' or 'O'):");
        scanf("%c ", &c.type);

        if((c.type) != 'P' && (c.type) != 'p' && (c.type) != 'O' && (c.type) != 'o') {
            printf("\nWrong value.");
            getchar();
        }

    } while ((c.type) != 'P' && (c.type) != 'p' && (c.type) != 'O' && (c.type) != 'o');

    printf("\nOverbalance:");
    scanf("%lf", &c.overbalance);

    return c;
}

void removeCustomer(int id) {

    int cId = 0;
    printf ("\nType the Client Account Number");
    scanf ("%d", &cId);

//    int hash = calcHash(id, dir->globalDepth);
//    int pos = searchInBucket(dir->key[hash], cId);
//    int line = dir->key[hash]->items[pos].line;
//
//    removeFromDir(dir, id);
//    removeFileLine(line);
}

void searchCustomer(int id) {

}

// Menu options
void printOptions() {
    clearScreen();
    printf("\n[1] - Register Customer\n");
    printf("[2] - Remove Customer\n");
    printf("[3] - Search Customer by Acc number\n");
    printf("[4] - Show Hash Table\n");
    printf("[0] - End Simulation\n");

    printf("\nEnter with your option: ");
}

void render(Dir *dir) {
    int n = (int) floor(pow(2, dir->globalDepth));
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

    Customer customer = {0, "teste", 'o', 21.5, };
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
                customer = newCostumer();
                insertOnDir(dir, &id, customer);
//                createFile(customer);
                id++;
                break;
            case 2:
                //check if is empty
                if(1)
                    removeFromDir(dir, id);
                else
                    printf("\nNo registered clients!\n");
                break;
            case 3:
                //check if is empty
                if(1)
                    printf("search completed");
                else
                    printf("\nNo registered clients!\n");
                break;
            case 4:
                //check if is empty
                if(1)
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