#ifndef DATA_STRUCTURE_STORAGE_H
#define DATA_STRUCTURE_STORAGE_H

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

// Structure of a file with an unique ID and the
// position of start at storage table to direct access
typedef struct File {
    char name[40];
    char content[200];
    unsigned size;
    unsigned id;
    unsigned fatStartPosition;
} File;

// Structure to represent a row of storage table
typedef struct FAT {
    StorageBlock *block;  // Logical address of storage block
    File *fileAddress;   // Point to file address
    int nextAddress;    // Next fat address of a file
} FAT;


Storage* initializeStorage(unsigned size);
unsigned fileSize(char *content);
unsigned createData(Storage *disk, FAT *fat, unsigned size, unsigned id);
void allocateFile(Storage *disk, FAT *fat, char *name, char *content, unsigned size, unsigned id);
FAT* initializeTable(unsigned storageSize);
void deallocateFile(Storage *disk, FAT *fat, int i);


#endif //DATA_STRUCTURE_STORAGE_H
