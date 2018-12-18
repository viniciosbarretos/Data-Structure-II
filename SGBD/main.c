#include <stdio.h>
#include <stdlib.h>
#include "libs/file.h"
#include "libs/customer.h"
#include "libs/hashing.h"
#include "libs/render.h"
#include "libs/utils.h"

void addCostumer(Dir *dir, int *id) {
    // Check if insertion can occurs
    if (freeSpaceAtDir > 0) {
        printHeader("Add a costumer");
        Customer costumer;

        // Get the costumer infos.
        costumer = getCostumer();

        // Insert costumer in dir.
        insertOnDir(dir, id, costumer);

        // Show message
        printHeader("File added!");

    } else {
        printHeader("Costumer can't be added. Directory is full");
    }
}

void deleteCustomer(Dir *dir) {
    int id;
    Item item;

    printHeader("Remove a costumer");

    // Get the costumer id.
    printf ("\nType the Client Account Number: ");
    scanf ("%d", &id);
    cleanBuffer();

    // Search for the item.
    item = searchFromDir(dir, id);

    // Remove or show error.
    if (item.id != -1) {
        removeFromDir(dir, id);
        printHeader("Costumer removed");
    } else {
        printHeader("Costumer not found");
    }
}

void searchCustomer(Dir *dir) {
    int id;
    Item item;
    Customer customer;

    printHeader("Search a costumer");

    // Get the costumer id.
    printf ("\nType the Client Account Number: ");
    scanf ("%d", &id);
    cleanBuffer();

    // Search for the item.
    item = searchFromDir(dir, id);

    // Remove or show error.
    if (item.id != -1) {
        customer = readCustomer(item.line);
        printCostumer(customer);
    } else {
        printHeader("Costumer not found");
    }
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

int main() {
    int id = 0;
    unsigned option;

    // Create the directory
    Dir *dir = newDirectory();

    // Create files directory.
    system("mkdir Files");

    do {
        // Clear the screen.
        clearScreen();

        // Print menu and get the option.
        printOptions();
        scanf("%d", &option);
        cleanBuffer();

        // Clear the screen for the option.
        clearScreen();

        switch (option) {
            case 0:
                printf("\n\nBye bye :)\n");
                break;
            case 1:
                addCostumer(dir, &id);
                id++;
                break;
            case 2:
                deleteCustomer(dir);
                break;
            case 3:
                searchCustomer(dir);
                break;
            case 4:
                renderHashTable(dir);
                break;
            default:
                printf("\nInvalid Option! Try again.");
        }

        printf("Press enter to continue...");
        getchar();

    } while (option);


    return 0;
}