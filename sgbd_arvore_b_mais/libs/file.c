#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

// Write where is "empty".
int saveRecord(Record record) {
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
            fseek(input, lineCounter * 79, SEEK_SET);

        } else {
            // Go to insertion point
            fseek(input, lineCounter * 79, SEEK_SET);

            // Save the customer infos.
//            fprintf(input, "0, %8d, %20s, %40s, %c\n", record.id, record.name, record.email, record.status);

            // Change isSaved flag
            isSaved = 1;

            // Go to the end of the file.
            fseek(input, 0, SEEK_END);
        }
    }

    if (!isSaved) {
        // Save the record infos.
//        fprintf(input, "1, %8d, %20s, %40s, %c\n", record.id, record.name, record.email, record.status);
    }

    // Close the file.
    fclose(input);

    return lineCounter;
}

// Put an block is free identifier "0" in the tuple.
int removeRecord(int line) {
    // Open file
    FILE *file = fopen("Files/SGBD.txt", "r+");

    if(!file) {
        return -1;
    }

    // Go to the line of the record.
    fseek(file, line * 79, SEEK_SET);

    // Alter flag.
    fprintf(file, "0");

    // Go to the end of the file.
    fseek(file, 0, SEEK_END);

    // Close the file.
    fclose(file);

    return 1;
}

// Returns the customer of the row.
Record readRecord(int line) {
    Record record;

    // Open the file.
    FILE *file = fopen("Files/SGBD.txt", "r");

    // Go to line of the record.
    fseek (file , line * 79 , SEEK_SET );

    // Read the record infos.
//    fscanf(file, "1, %d, %[^,], %s, %c\n", &record.id, record.name, &record.email, &record.status);

    // Close the file.
    fclose(file);

    // Return the record.
    return record;
}




