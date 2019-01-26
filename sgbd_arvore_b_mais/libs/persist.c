//
// Created by vinny on 1/25/2019.
//
#include "persist.h"

//Recover the SGBD state by the file.
int hydrateFile(node *root) {
    FILE *file = fopen("Files/SGBD.txt", "r");

    int aux; //Verifies if is an existing data, "1" Copies and "0" Jumps
    Student student;


    if(file) {
        while(fscanf(file, "%d, %d, %[^,], %s, %c\n", &aux, &student.id, student.name, student.email, &student.status) == 1) {
        // TODO: Change insertion function, can't copy students again in file.
            if (aux)
                root = insert(root, student.id, student);
        }
        fclose(file);
        return 1;
    }
    else
        return 0;
}