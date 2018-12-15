//
// Created by vinicius on 08/12/18.
//

#ifndef SGBD_FILE_H
#define SGBD_FILE_H

    void createFile (unsigned account_number, char *name, char *customer_type, double overbalance);
    int lineCounter (unsigned accountNumber);
    void removeFileLine(int line);
    double getCustomerOverBalancing (int line, int line_size);
    char getCustomerType (int line, int line_size);
    char * getCustomerName (int line, int line_size);
    int getCustomerAccountNumber (int line, int line_size);
#endif //SGBD_FILE_H
