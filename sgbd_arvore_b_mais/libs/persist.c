//
// Created by vinny on 1/25/2019.
//
#include "persist.h"

//Recover the SGBD state by the file.
int hydrateFile(Node *root) {
    FILE *file = fopen("SGBD.txt", "r");
    int lineCounter=0;

    int aux; //Verifies if is an existing data, "1" Copies and "0" Jumps
    int id;

    if(file) {
        while(fscanf(file, "%d, %d", &aux, &id) == 2) {
            if (aux)
                root = insert(root, id, lineCounter);
            fseek(file, 74, SEEK_CUR);
            lineCounter++;
        }
        fclose(file);
        return 1;
    }
    else
        return 0;
}