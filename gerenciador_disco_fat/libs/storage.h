#ifndef DATA_STRUCTURE_STORAGE_H
#define DATA_STRUCTURE_STORAGE_H
#include <stdio.h>

// Each block have 1w size and a logical address
typedef struct StorageBlock {
    unsigned logicalAddress;
    unsigned fileID;
} StorageBlock;

// Structure of a disk, containing data blocks
// and a counter specifying your available space
typedef struct Storage {
    StorageBlock *data;
    unsigned availableSpace;
} Storage;

/*
// Structure of a file with an unique ID and the
// position of start at storage table to direct access
typedef struct File_old_ {
    char name[40];
    char content[200];
    unsigned size;
    unsigned id;
    unsigned fatStartPosition;
} File_old_;
*/

typedef struct Metadata {
    char *name;
    unsigned size;
    unsigned id;
    // Security
    unsigned owner;
    short unsigned protection;
    // Time controllers
    int creationTime;
    int uptateTime;
    int accessTime;
} Metadata;


// Structure of files list and his fragments
typedef struct Node {
    unsigned startPosition;
    unsigned size;
    struct Node *next;
    Metadata *metadata;
} Node;

// List of nodes.
typedef struct NodeList {
    struct Node *start;
    struct Node *end;
} NodeList;

/*
// Structure to represent a row of storage table
typedef struct FAT_old_ {
    StorageBlock *block;  // Logical address of storage block
    File *fileAddress;   // Point to file address
    int nextAddress;    // Next fat address of a file
} FAT_old_;
*/

NodeList *newNodeList();
NodeList *nodeListInsertEnd(NodeList *nodeList, Node *node);
Storage* initializeStorage(unsigned size);
unsigned fileSize(char *content);
void allocateFile(Storage *storage, NodeList **list, unsigned diskSize, unsigned id, char *name, char *content, unsigned size);
int deallocateFile(Storage *storage, NodeList **list, unsigned id);
//void dehydrate(Storage *storage, NodeList *nodeList);
//void dehydrateNodeList(FILE *file, NodeList *nodeList);
//void dehydrateStorage(FILE *file, Storage *storage);
//Storage* hydrateStorage(FILE *file, Storage *storage);
//NodeList* hydrateNodeList(FILE *file);
//unsigned createData(Storage *disk, FAT *fat, unsigned size, unsigned id);
//void allocateFile(Storage *disk, FAT *fat, char *name, char *content, unsigned size, unsigned id);
//FAT* initializeTable(unsigned storageSize);
//void deallocateFile(Storage *disk, FAT *fat, int i);


#endif //DATA_STRUCTURE_STORAGE_H
