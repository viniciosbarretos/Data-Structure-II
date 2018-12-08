#ifndef SGBD_CUSTOMER_H
#define SGBD_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct customer {
    unsigned accountNumber;
    char *name;
    char customerType;
    unsigned overbalance;
};
typedef struct bucket {

};

void registerCustomer();
void removeCustomer();
void searchCustomer();

#endif //SGBD_CUSTOMER_H
