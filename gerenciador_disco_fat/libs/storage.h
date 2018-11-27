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

NodeList *newNodeList();
NodeList *nodeListInsertEnd(NodeList *nodeList, Node *node);
Storage* initializeStorage(unsigned size);
unsigned fileSize(char *content);
void allocateFile(Storage *storage, NodeList **list, unsigned diskSize, unsigned id, char *name, char *content, unsigned size);
int deallocateFile(Storage *storage, NodeList **list, unsigned id);
void eraseDisk (Storage *storage, NodeList *nodeList, int size);
char * getFileContent (char name[]);


#endif //DATA_STRUCTURE_STORAGE_H
