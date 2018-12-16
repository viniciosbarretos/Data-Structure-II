#include <stdlib.h>
#include "file.h"
#include "stdio.h"
#include "string.h"

//Saving and formatting real file in disk.
void createFile(unsigned line, unsigned account_number, char *name, char customer_type, double overbalance) {

    FILE *file;

    //Setting directory of file
    char dir[50] = "Files/";
    strcat(dir, "SGBD.txt");

    file = fopen(dir, "a");

    //Writing file
    fprintf(file, "%d, %d, %s, %c, %f", line, account_number, name, customer_type, overbalance);
    fclose(file);
}

//Returns line where customer was registered
int lineCounter(unsigned accountNumber) {
    int counter = 0;
    int aux_account;

    FILE *file;

    file = fopen("Files/SGBD.txt", "r");

    do {
        int aux;

        fscanf(file, "%d, %d", &aux, &aux_account);

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

//Write file in first blank space.
void createFile2 (unsigned line, unsigned account_number, char *name, char customer_type, double overbalance) {
    FILE *input = fopen("Files/SGBD.txt", "r");
    FILE *output = fopen("Files/output.txt", "w");
    int flag = 0;

    char text[1000] = "";
    int line_progress = 1;
    while(fgets(text, 1000, input) != NULL) {
        if(!strcmp(text, "\n") && !flag) {
            fprintf(output, "%d, %d, %s, %c, %f", line, account_number, name, customer_type, overbalance);
            flag = 1; //Customer added.

        } else { //Copy old file
            fputs(text, output);
        }
        memset(text, 0, sizeof(char) * 1000);
    }
    fclose(input);
    fclose(output);
    remove(input);
    rename("Files/output.txt", "Files/SGBD.txt");
}