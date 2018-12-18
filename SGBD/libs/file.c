#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "customer.h"

// Write where is "empty".
int saveCostumer(Customer customer) {
    int notFree, lineCounter, lineCustomer;

    // Init variables.
    lineCounter = 0;
    lineCustomer = -1;

    // Open file.
    FILE *input = fopen("Files/SGBD.txt", "w+");

    if (!input) {
        return -1;
    }

    while ( fscanf(input, "%d", &notFree) ) {

        // Verifying free spaces in SGBD file. notFree = 0;
        if (notFree) {
            // Go to line above.
            fseek(input, lineCounter * 67, SEEK_SET);
            lineCounter++;

        } else {
            // Save the customer infos.
            fprintf(input, "1, %8d, %40s, %c, %8.2lf\n", customer.id, customer.name, customer.type, customer.overbalance);

            // Save the line that was saved.
            lineCustomer = lineCounter;

            // Go to the end of the file.
            fseek(input, 0, SEEK_END);
        }
    }

    // Close the file.
    fclose(input);

    return lineCustomer;
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




