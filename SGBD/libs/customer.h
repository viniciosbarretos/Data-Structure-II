#ifndef SGBD_CUSTOMER_H
#define SGBD_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct customer {
    unsigned accountNumber;
    char *name;
    char *customerType;
    unsigned overbalance;
} customer;

typedef struct array[4] {
    unsigned id;
    customer *customerx;
} array;

typedef struct bucket {
    unsigned localDepth;
    struct array[4];
} bucket;

typedef struct directory {
    unsigned globalDepth;
    bucket *bucketx;
} directory;

double hashFunction(unsigned accountNumber, unsigned globalDepth);
void newDirectory();
void duplicateDirectory();
void newBucket();
void duplicateBucket();
customer newCostumer();
void registerCustomer();
void removeCustomer();
void searchCustomer();

#endif //SGBD_CUSTOMER_H
