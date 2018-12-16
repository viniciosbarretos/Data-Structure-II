//
// Created by vinicius on 08/12/18.
//

#ifndef SGBD_FILE_H
#define SGBD_FILE_H
#include "customer.h"


    int createFile (unsigned account_number, char *name, char customer_type, double overbalance);
    int lineCounter (unsigned accountNumber);
    void removeFileLine(int line);
    Customer * getCustomer (int line, int line_size);
#endif //SGBD_FILE_H
