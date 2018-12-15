//
// Created by vinicius on 08/12/18.
//
#include <stdlib.h>
#include "file.h"
#include "stdio.h"
#include "string.h"

//Saving and formatting real file in disk.
//void createFile2 (unsigned line, unsigned account_number, char *name, char *customer_type, double overbalance) {
//
//    FILE *file;
//
//    //Setting directory of file
//    char dir[50] = "Files/";
//    strcat(dir, "SGBD.txt");
//
//    file = fopen(dir, "a");
//
//    //Writing file
//    fprintf(file, "%d, %d, %s, %c, %ld", line, account_number, name, customer_type, overbalance);
//    fclose(file);
//}

//Write where is "empty".
void createFile (unsigned account_number, char *name, char *customer_type, double overbalance) {
    FILE *input = fopen("Files/SGBD.txt", "r");
    FILE *output = fopen("Files/output.txt", "w");
    int flag = 0;
    int notEmpty;

    char text[1000] = "";
    while(fgets(text, 1000, input) != NULL) {
        fscanf(input, "%d", &notEmpty);
        if(!notEmpty && !flag) {
            fprintf(output, "1, %8d, %40s  %c, %8.2f\n", account_number, name, customer_type, overbalance);
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

//Put an blank space identifier "0" in a tuple.
void removeFile (int line) {

    FILE *input = fopen("Files/SGBD.txt", "r");
    FILE *output = fopen("Files/output.txt", "w");
    char text[1000] = "";
    char customer_removed[1000] = "";
    int line_progress = 1;
    while(fgets(text, 1000, input) != NULL) {
        if(line_progress != line) {
            fputs(text, output);
        }
        //Putting '0' to identify free space.
        else {
            strcpy(customer_removed, text);
            customer_removed[0] = 0;
            fputs(customer_removed, output);
        }

        memset(text, 0, sizeof(char) * 1000);
        line_progress++;
    }
    fclose(input);
    fclose(output);
    remove("Files/SGBD.txt");
    rename("Files/output.txt", "Files/SGBD.txt");
}

//Returns a customer account number.
int getCustomerAccountNumber (int line, int line_size) {
//line_size = 67;
    char query[200];
    int accountNumber;
    char name[40], type;
    double overBalancing;

    FILE *file;

    file = fopen("TESTANDO.txt", "r");
    fseek (file , line * line_size , SEEK_SET );
    fscanf(file, "1, %d, %s %c, %lf", &accountNumber, name, &type, &overBalancing);
    fclose(file);

    return accountNumber;
}

//Returns a customer name.
char * getCustomerName (int line, int line_size) {
//line_size = 67;
    char query[200];
    int accountNumber;
    char name[40], type;
    double overBalancing;

    FILE *file;

    file = fopen("TESTANDO.txt", "r");
    fseek (file , line * line_size , SEEK_SET );
    fscanf(file, "1, %d, %s %c, %lf", &accountNumber, name, &type, &overBalancing);
    fclose(file);

    return name;
}

//Returns a customer type.
char getCustomerType (int line, int line_size) {
//line_size = 67;
    char query[200];
    int accountNumber;
    char name[40], type;
    double overBalancing;

    FILE *file;

    file = fopen("TESTANDO.txt", "r");
    fseek (file , line * line_size , SEEK_SET );
    fscanf(file, "1, %d, %s %c, %lf", &accountNumber, name, &type, &overBalancing);
    fclose(file);

    return type;
}

//Returns a customer over balancing.
double getCustomerOverBalancing (int line, int line_size) {
//line_size = 67;
    char query[200];
    int accountNumber;
    char name[40], type;
    double overBalancing;

    FILE *file;

    file = fopen("TESTANDO.txt", "r");
    fseek (file , line * line_size , SEEK_SET );
    fscanf(file, "1, %d, %s %c, %lf", &accountNumber, name, &type, &overBalancing);
    fclose(file);

    return overBalancing;
}




