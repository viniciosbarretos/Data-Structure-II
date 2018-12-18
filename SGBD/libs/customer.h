#ifndef SGBD_CUSTOMER_H
#define SGBD_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    unsigned id;
    char *name;
    char type;
    double overbalance;
} Customer;

Customer getCostumer();

#endif //SGBD_CUSTOMER_H
