#ifndef SGBD_FILE_H
#define SGBD_FILE_H
#include "bplustree.h"

int saveRecord(Record record);
int removeRecord(int line);
Record readRecord(int line);

#endif //SGBD_FILE_H
