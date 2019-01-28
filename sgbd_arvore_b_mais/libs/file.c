#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

// Write where is "empty".
int saveStudent(Student student) {
    int notFree, lineCounter, isSaved;

    // Init variables.
    lineCounter = 0;
    isSaved = 0;

    // Open file.
    FILE *input = fopen("SGBD.txt", "r+");

    if (!input) {
        // Create file.
        input = fopen("SGBD.txt", "w+");

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
            fseek(input, lineCounter * 84, SEEK_SET);

        } else {
            // Go to insertion point
            fseek(input, lineCounter * 84, SEEK_SET);

            // Save the customer infos.
            fprintf(input, "1, %8d, %20s, %3d, %40s, %c\n", student.id, student.name, student.age, student.email, student.status);

            // Change isSaved flag
            isSaved = 1;

            // Go to the end of the file.
            fseek(input, 0, SEEK_END);
        }
    }

    if (!isSaved) {
        // Save the student infos.
        fprintf(input, "1, %8d, %20s, %3d, %40s, %c\n", student.id, student.name, student.age, student.email, student.status);
    }

    // Close the file.
    fclose(input);

    return lineCounter;
}

// Put an block is free identifier "0" in the tuple.
int removeStudent(int line) {
    // Open file
    FILE *file = fopen("SGBD.txt", "r+");

    if(!file) {
        return -1;
    }

    // Go to the line of the record.
    fseek(file, line * 84, SEEK_SET);

    // Alter flag.
    fprintf(file, "0");

    // Go to the end of the file.
    fseek(file, 0, SEEK_END);

    // Close the file.
    fclose(file);

    return 1;
}

// Returns the customer of the row.
Student readStudent(int line) {
    Student student;

    // Open the file.
    FILE *file = fopen("SGBD.txt", "r");

    // Go to line of the record.
    fseek (file , line * 84 , SEEK_SET );

    // Read the record infos.
    fscanf(file, "1, %d, %[^,], %d, %s, %c\n", &student.id, student.name, &student.age, student.email, &student.status);

    // Close the file.
    fclose(file);

    // Return the record.
    return student;
}

// Set student data
int setStudent(int line, Student student) {

    // Open the file.
    FILE *file = fopen("SGBD.txt", "r+");

    if(file) { //If file was opened.

        // Go to line of the record.
        fseek(file, line * 84, SEEK_SET);

        // set the record infos.
        fprintf(file, "1, %8d, %20s, %3d, %40s, %c\n", student.id, student.name, student.age, student.email, student.status);

        // Close the file.
        fclose(file);
        return 1;
    }

    else //If can't open file.
        return 0;
}

void showStudentList() {
    FILE *file = fopen("SGBD.txt", "r");
    int id;
    char name[20];
    char email[40];
    int age;
    int aux;
    char status;
    if(file == NULL)
        printf("Empty list!");
    else {
        while (fscanf(file, "%d, %d, %[^,], %d, %[^,], %c\n", &aux, &id, name, &age, email, &status) == 6) {
            if(aux) {
                printf("Student %d: \n\tName: %s\n\tAge: %d\n\te-mail: %s\n\tStatus: %c\n", id, name, age, email, status);
            }
        }
        fclose(file);
    }
}