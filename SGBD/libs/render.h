#ifndef SGBD_RENDER_H
#define SGBD_RENDER_H

#include "hashing.h"
#include "customer.h"

void clearScreen();
void printHeader(const char *str);
void renderHashTable(Dir *dir);
void printCostumer(Customer customer);

#endif //SGBD_RENDER_H
