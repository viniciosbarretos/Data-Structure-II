//
// Created by vinicius on 08/12/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "customer.h"

//Write where is "empty".
int createFile (Customer customer) {

    int noEmpty = 1;
    int lineCounter = 0;
    int lineCustomer = -1;

    FILE *input = fopen("Files/SGBD.txt", "w+");

    if(!input) {
        return -1;
    }
    else {
        while(fscanf(input, "%d", &noEmpty)) {

            //Verifying free spaces in SGBD file. notEmpty = 0;
            fscanf(input, "%d", &noEmpty);
            if(!noEmpty) {
                fprintf(input, "1, %8d, %40s, %c, %8.2lf\n", customer.id, customer.name, customer.type, customer.overbalance);
                lineCustomer = lineCounter;
                fseek(input, 0, SEEK_END);

            } else {
                fseek(input, lineCounter * 67, SEEK_SET);
                lineCounter++;
            }
        }
    }
    fclose(input);

    return lineCustomer;
}

//Put an blank space identifier "0" in a tuple.
int removeFile (int line) {
    FILE *file = fopen("Files/SGBD.txt", "r+");

    if(!file) {
        return -1;
    }
    else {
        fseek(file, line * 67, SEEK_SET);
        fprintf(file, "0");
        fseek(file, 0, SEEK_END);
    }
    fclose(file);
    return 1;
}

//Returns a customer.
Customer * getCustomer (int line, int line_size) {
//line_size = 67;
//line have to start in 0.

    Customer *customer = malloc(sizeof(Customer));
    unsigned accountNumber;
    char name[40], type;
    double overBalancing;

    FILE *file;

    file = fopen("Files/SGBD.txt", "r");
    fseek (file , line * line_size , SEEK_SET );
    fscanf(file, "1, %d, %[^,], %c, %lf", &accountNumber, name, &type, &overBalancing);
    fclose(file);

    customer->id = accountNumber;
    strcpy(customer->name, name);
    customer->type = type;
    customer->overbalance = overBalancing;

    return customer;
}




