//
// Created by vinicius on 08/12/18.
//

#ifndef SGBD_HASHING_H
#define SGBD_HASHING_H
#include "math.h"

typedef struct bucket_dir {
    unsigned global_depth;
    int *key;
}bucket_dir;

typedef struct id_line {
    unsigned id; //Account number
    unsigned line; //Line in file
}id_line;

typedef struct bucket {
    unsigned localDepth;
    id_line * idLine[4];
} bucket;

int hashFunction(unsigned accountNumber, unsigned globalDepth);
void newDirectory();
void duplicateDirectory();
void newBucket();
void duplicateBucket();

#endif //SGBD_HASHING_H
