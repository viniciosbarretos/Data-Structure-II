#ifndef SGBD_HASHING_H
#define SGBD_HASHING_H
#include "math.h"
#include "customer.h"

typedef struct Item {
    int id; // Account number
    unsigned line; // Line in file
} Item;

typedef struct Bucket {
    unsigned localDepth;
    Item items[4];
} Bucket;

typedef struct Dir {
    unsigned globalDepth;
    struct Bucket **key;
} Dir;


Dir * newDirectory();
void insertOnDir(Dir *dir, int *id, Customer c);
void removeFromDir(Dir *dir, int id);

//int hashFunction(unsigned accountNumber, unsigned globalDepth);
//void newDirectory();
//void duplicateDirectory();
//void newBucket();
//void duplicateBucket();

#endif //SGBD_HASHING_H
