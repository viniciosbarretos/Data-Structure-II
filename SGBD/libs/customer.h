#ifndef SGBD_CUSTOMER_H
#define SGBD_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    unsigned id;
    char *name;
    char *customerType;
    double overbalance;
} Customer;

Customer * newCostumer();
void registerCustomer();
void removeCustomer();
void searchCustomer();

#endif //SGBD_CUSTOMER_H
