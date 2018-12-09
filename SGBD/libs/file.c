//
// Created by vinicius on 08/12/18.
//
#include <stdlib.h>
#include "file.h"
#include "stdio.h"
#include "string.h"

//Saving and formatting real file in disk.
void createFile (unsigned line, unsigned account_number, char *name, char *customer_type, double overbalance) {

    FILE *file;

    //Setting directory of file
    char dir[50] = "Files/";
    strcat(dir, "SGBD.txt");

    file = fopen(dir, "a");

    //Writing file
    fprintf(file, "%d, %d, %s, %c, %ld", line, account_number, name, customer_type, overbalance);
    fclose(file);
}

//Returns line where customer was registered
int lineCounter (unsigned accountNumber) {
    int counter = 0;
    int aux_account;

    FILE *file;

    file = fopen("Files/SGBD.txt", "r");

    do {
        int aux;

        fscanf(file, "%d, %d",aux, aux_account);

        counter++;
    } while(!feof(file) && aux_account != accountNumber);

    return counter;
}

//Removes a file line and deletes blank spaces, creating a new file and deleting the old one.
void removeFileLine (int line) {
    FILE *input = fopen("Files/SGBD.txt", "r");
    FILE *output = fopen("Files/output.txt", "w");
    char text[1000] = "";
    int line_progress = 1;
    while(fgets(text, 1000, input) != NULL) {
        if(line_progress != line) {
            fputs(text, output);
        }
        //***Putting blank spaces, (if we don't put 'else' we lose blank spaces) ***
//        else {
//            fputs('\n', output);
//        }
        memset(text, 0, sizeof(char) * 1000);
        line_progress++;

    }
    fclose(input);
    fclose(output);
    remove(input);
    rename("Files/output.txt", "Files/SGBD.txt");
}