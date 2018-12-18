#include <stdlib.h>
#include <math.h>
#include "hashing.h"
#include "customer.h"

#define minDepth 2
#define maxDepth 3
#define defaultBucketSize 4
#define false 0
#define true 1

#define max(a, b) ((a)>(b) ? (a) : (b))

// Alloc a new bucket and return a pointer to then.
Bucket * newBucket() {
    int i;

    // Allocate memory for the bucket.
    Bucket *newBucket = (Bucket *) malloc(sizeof(Bucket));
    newBucket->localDepth = minDepth;

    // Zero fill the bucket items.
    for (i = 0; i<4; i++) {
        newBucket->items[i].id = -1;
        newBucket->items[i].line = 0;
    }

    return newBucket;
}

// Alloc a new directory and return a pointer to then.
Dir * newDirectory() {
    int i, n;

    // Allocate memory for the directory.
    Dir *newDir = (Dir *) malloc(sizeof(Dir));

    // Calc the size of the dir.
    n = (int) pow(2, minDepth);

    // Initialize the directory.
    newDir->globalDepth = minDepth;
    newDir->itemsSaved = 0;
    newDir->key = malloc(sizeof(Bucket*) * n);

    // Create the first buckets.
    for (i = 0; i < n; i++) {
        newDir->key[i] = newBucket();
    }

    return newDir;
}

int freeSpaceAtDir(Dir *dir) {
    return ((int) pow(2, dir->globalDepth) * 4) - dir->itemsSaved;
}

// Calc the hash.
int calcHash(int n, int depth) {
    int expo = (int) floor(pow(2, depth));
    return n % expo;
}

// Get the number of elements in a bucket.
int getBucketSize(Bucket *bucket) {
    int i = 0;
    // Count the number of valid items in the bucket.
    while (i < defaultBucketSize && bucket->items[i].id != -1) {
        i++;
    }

    return i;
}

// Increase the dir depth and remake the pointers.
Dir * increaseDir(Dir *dir) {
    int i, n;

    // Increase the globalDeath.
    n = (int) floor(pow(2, dir->globalDepth));
    dir->globalDepth++;

    // Re alloc the memory of the directory
    dir->key = realloc(dir->key, sizeof(Bucket*) * (n * 2));

    // Re point directory to bucket.
    for (i = 0; i < n; i++) {
        dir->key[i+n] = dir->key[i];
    }

    return dir;
}

// Decrease the dir depth and remake the pointers.
Dir * decreaseDir(Dir *dir) {
    int n;

    // Decrease the globalDeath.
    dir->globalDepth--;
    n = (int) floor(pow(2, dir->globalDepth));

    // Re alloc the memory of the directory
    dir->key = realloc(dir->key, sizeof(Bucket*) * n);

    return dir;
}

// Insert an element in a bucket.
Bucket * insertOnBucket(Bucket *bucket, Customer c, int position) {
    // Todo save on file
    unsigned fileLine = 45;

    // Save item
    bucket->items[position].id = c.id;
    bucket->items[position].line = fileLine;

    return bucket;
}


// Search an element in a bucket.
int searchInBucket(Bucket *bucket, int id) {
    int i, length;

    // Get the bucket length.
    length = getBucketSize(bucket);

    // Search item on bucket elements and return the position.
    for (i = 0; i < length; i++) {
        if (bucket->items[i].id == id) {
            return i;
        }
    }

    // Item not found.
    return -1;
}

// Remove an element from a bucket.
Bucket * removeFromBucket(Bucket *bucket, int position) {
    int i;
    // Todo remove from file

    // Shift elements on bucket.
    for (i = position; i < defaultBucketSize - 1; i++) {
        bucket->items[i] = bucket->items[i+1];
    }

    // Clean the last element.
    bucket->items[i].id = -1;
    bucket->items[i].line = 0;

    return bucket;
}

// Split the bucket and return the new one.
Bucket * splitBucket(Dir *dir, Bucket *bucket) {
    int i, k, hash, length;
    Bucket *aux;

    // Initialize the insertion position controller for the new bucket.
    k = 0;

    // Allocate memory for the new bucket.
    Bucket *bucket2 = newBucket();

    length = getBucketSize(bucket);

    // Re calc the hash for all the elements in the bucket.
    for (i = 0; i < length; i++) {

        hash = calcHash(bucket->items[i].id, dir->globalDepth);
        aux = dir->key[hash];

        // If the data goes to the new bucket.
        if (aux != bucket) {
            // Insert data on new bucket.
            bucket2->items[k].id = bucket->items[i].id;
            bucket2->items[k].line = bucket->items[i].line;

            // Remove the data from the old bucket.
            bucket = removeFromBucket(bucket, i);

            // Increase the new bucket insertion position controller.
            k++;
        }
    }

    // Alter the depth of the buckets
    bucket->localDepth++;
    bucket2->localDepth++;

    return bucket2;
}

// Get the max depth of all buckets.
int getMaxDepthFromBuckets(Dir *dir) {
    int i, pass, vMax=0;

    // Get the number of buckets
    pass = (int) pow(2, dir->globalDepth);

    // Get the max element.
    for (i=0; i < pass; i++) {
        vMax = max(vMax, dir->key[i]->localDepth);
    }

    return vMax;
}

// Insert an element in a dir and, when necessary, split the bucket or increase the dir depth.
void insertOnDir(Dir *dir, int *id, Customer c) {
    int hash, bucketSize;
    int resolved = false;

    Bucket *bucket, *addBucket;

    while(!resolved) {
        // Set the customer id.
        c.id = (unsigned) (*id);

        // Get the bucket for the hash of the item
        hash = calcHash(c.id, dir->globalDepth);
        bucket = dir->key[hash];

        // Create the bucket if need.
        if (!bucket) {
            bucket = newBucket();
            dir->key[hash] = bucket;
        }

        // Get the number of items in the bucket.
        bucketSize = getBucketSize(bucket);

        // Check if item can be inserted on bucket.
        if (bucketSize < defaultBucketSize) {
            insertOnBucket(bucket, c, bucketSize);
            dir->itemsSaved++;
            resolved = true;
        }
        // Check if is possible to split the bucket.
        else if (bucket->localDepth < dir->globalDepth){
            // Split the bucket.
            addBucket = splitBucket(dir, bucket);

            // Save bucket in the dir.
            int pass = (int) pow(2, dir->globalDepth-1);
            dir->key[hash + pass] = addBucket;
        }
        // Check if is possible to increase the dir.
        else if (dir->globalDepth < maxDepth) {
            // Increase the size of the dir.
            dir = increaseDir(dir);
        }
        // Change data structure is not agree, alter the id
        else {
            // Increase the id number and try again;
            (*id)++;
        }
    }
}

Item searchFromDir(Dir *dir, int id) {
    int hash, p;
    Bucket *bucket;

    // Get the bucket of the element
    hash = calcHash(id, dir->globalDepth);
    bucket = dir->key[hash];

    // Get the position
    p = searchInBucket(bucket, id);

    // If not found, return a blank item.
    if (p == -1) {
        Item i = {-1, 0};
        return i;
    }

    // Return the item.
    return dir->key[hash]->items[p];
}

// Remove a element from dir and, when necessary, merge buckets or reduce the dir depth.
void removeFromDir(Dir *dir, int id) {
    int hash, p;
    Bucket *bucket;

    // Get the bucket of the element
    hash = calcHash(id, dir->globalDepth);
    bucket = dir->key[hash];

    // Remove from vector
    p = searchInBucket(bucket, id);
    if (p != -1) {
        removeFromBucket(bucket, p);
        dir->itemsSaved--;
    }

    // Check for a merge.
    if (getBucketSize(bucket) == 0) {
        // Deleting the directory.
        free(bucket);

        int pass = (int) floor(pow(2, dir->globalDepth-1));

        // Re-point to the bucket.
        if (hash < pass / 2) {
            dir->key[hash] = dir->key[hash+pass];
        } else {
            dir->key[hash] = dir->key[hash-pass];
        }

        // Check for a directory reduction.
        if (getMaxDepthFromBuckets(dir) < dir->globalDepth) {
            decreaseDir(dir);
        }
    }

}

/*
 * Extra functions for render
 */

// Return the original key if it's position is a pointer to the same bucket.
// If it's not happens, return -1.
int bucketAppearsBefore(Dir *dir, int position) {
    int i;

    for (i = 0; i < position; i++) {
        if (dir->key[i] == dir->key[position]) {
            return i;
        }
    }

    return -1;
}

// Return the quantity of different buckets in a dir.
int differentBucketsInDir(Dir *dir) {
    int i, size, counter;

    // Initialize variables
    size = (int) floor(pow(2, dir->globalDepth));
    counter = 0;

    // Iterate over dir
    for (i = 0; i < size; i++) {
        if (bucketAppearsBefore(dir, i) == -1) {
            counter++;
        }
    }

    return counter;
}


