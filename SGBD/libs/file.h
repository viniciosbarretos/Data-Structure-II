#ifndef SGBD_FILE_H
#define SGBD_FILE_H
#include "customer.h"

int saveCostumer(Customer customer);
int removeCostumer(int line);
Customer readCustomer(int line);

#endif //SGBD_FILE_H
