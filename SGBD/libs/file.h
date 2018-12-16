#ifndef SGBD_FILE_H
#define SGBD_FILE_H

    void createFile(unsigned line, unsigned account_number, char *name, char customer_type, double overbalance);
    int lineCounter(unsigned accountNumber);
    void removeFileLine(int line);
#endif //SGBD_FILE_H
