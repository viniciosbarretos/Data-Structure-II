#ifndef SGBD_CUSTOMER_H
#define SGBD_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>
//#include "hashing.h"

typedef struct Customer {
    unsigned id;
    char *name;
    char *customerType;
    double overbalance;
} Customer;

Customer * newCostumer();
void registerCustomer(int id);
void removeCustomer(int id);
void searchCustomer(int id);

#endif //SGBD_CUSTOMER_H
