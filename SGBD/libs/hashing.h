#ifndef SGBD_HASHING_H
#define SGBD_HASHING_H
#include <math.h>
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
    unsigned itemsSaved;
    struct Bucket **key;
} Dir;


Dir * newDirectory();
int freeSpaceAtDir(Dir *dir);
void insertOnDir(Dir *dir, int *id, Customer c);
Item searchFromDir(Dir *dir, int id);
void removeFromDir(Dir *dir, int id);
int calcHash(int n, int depth);
int searchInBucket(Bucket *bucket, int id);
int bucketAppearsBefore(Dir *dir, int position);
int differentBucketsInDir(Dir *dir);

#endif //SGBD_HASHING_H
