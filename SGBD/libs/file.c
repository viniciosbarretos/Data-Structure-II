#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "customer.h"

// Write where is "empty".
int saveCostumer(Customer customer) {
    int notFree, lineCounter, isSaved;

    // Init variables.
    lineCounter = 0;
    isSaved = 0;

    // Open file.
    FILE *input = fopen("Files/SGBD.txt", "r+");

    if (!input) {
        // Create file.
        input = fopen("Files/SGBD.txt", "w+");

        // Can't manage files, exit.
        if (!input) {
            return -1;
        }
    }


    while ( fscanf(input, "%d", &notFree) == 1) {

        // Verifying free spaces in SGBD file. notFree = 0;
        if (notFree) {
            // Go to line above.
            lineCounter++;
            fseek(input, lineCounter * 67, SEEK_SET);

        } else {
            // Go to insertion point
            fseek(input, lineCounter * 67, SEEK_SET);

            // Save the customer infos.
            fprintf(input, "1, %8d, %40s, %c, %8.2lf\n", customer.id, customer.name, customer.type, customer.overbalance);

            // Change isSaved flag
            isSaved = 1;

            // Go to the end of the file.
            fseek(input, 0, SEEK_END);
        }
    }

    if (!isSaved) {
        // Save the customer infos.
        fprintf(input, "1, %8d, %40s, %c, %8.2lf\n", customer.id, customer.name, customer.type, customer.overbalance);
    }

    // Close the file.
    fclose(input);

    return lineCounter;
}

// Put an block is free identifier "0" in the tuple.
int removeCostumer(int line) {
    // Open file
    FILE *file = fopen("Files/SGBD.txt", "r+");

    if(!file) {
        return -1;
    }

    // Go to the line of the customer.
    fseek(file, line * 67, SEEK_SET);

    // Alter flag.
    fprintf(file, "0");

    // Go to the end of the file.
    fseek(file, 0, SEEK_END);

    // Close the file.
    fclose(file);

    return 1;
}

// Returns the customer of the row.
Customer readCustomer(int line) {
    Customer customer;

    // Open the file.
    FILE *file = fopen("Files/SGBD.txt", "r");

    // Go to line of the customer.
    fseek (file , line * 67 , SEEK_SET );

    // Read the customer infos.
    fscanf(file, "1, %d, %[^,], %c, %lf", &customer.id, customer.name, &customer.type, &customer.overbalance);

    // Close the file.
    fclose(file);

    // Return the customer.
    return customer;
}




