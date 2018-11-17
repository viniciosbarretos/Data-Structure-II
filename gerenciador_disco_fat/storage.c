#include <stdlib.h>
#include <string.h>
#include "storage.h"

// This is like a disk formatting and mount
Storage* initializeStorage(unsigned size) {

    Storage *storage = (Storage *) malloc (sizeof(Storage));
    storage->data = malloc (sizeof(StorageBlock) * size);
    storage->availableSpace = size;

    for (unsigned i = 0; i<size; i++) {
        storage->data[i].fileID = 0;
        storage->data[i].logicalAddress = i;
    }

    return storage;
}

// Initialize the table creating an array of FAT structure.
// Each position of array represents a table row with direct access.
FAT* initializeTable(unsigned storageSize) {
    FAT *fat = malloc (sizeof(FAT) * storageSize);
    for (unsigned i=0; i<storageSize; i++) {
        fat[i].block = NULL;
        fat[i].fileAddress = NULL;
        fat[i].nextAddress = 0;
    }
    return fat;
}

// Count file size based at amount of character typed
unsigned fileSize(char *content) {
    unsigned size = (unsigned) (strlen(content) / 8 + 2);
    return (size < 20) ? size : 20;
}

// Insert data into storage and reference in table
unsigned createData(Storage *disk, FAT *fat, unsigned size, unsigned id) {
    unsigned blockAdded = 0, i = 0, first=0;
    int aux = - 1;

    // i<storageSize don't is checked because this code
    // will only execute if storage have available space
    while (blockAdded<size) {
        if(fat[i].block == NULL) {
            disk->data[i].fileID = id;
            fat[i].block = &disk->data[i];
            fat[i].nextAddress = -1;

            if(!blockAdded) {
                first = i;
            }
            else {
                fat[aux].nextAddress = i;
            }

            aux = i;
            blockAdded++;
            disk->availableSpace--;
        }
        i++;
    }

    // First variable is the position that files start on table
    return first;
}

// Create file content and call createData function to insert it into storage
void allocateFile(Storage *disk, FAT *fat, char *name, char *content, unsigned size, unsigned id) {
    File *newFile = malloc (sizeof (File));
    strcpy(newFile->name, name);
    strcpy(newFile->content, content);
    newFile->id = id;
    newFile->size = size;
    newFile->fatStartPosition = createData(disk, fat, size, newFile->id);
    fat[newFile->fatStartPosition].fileAddress = newFile;
}


// Remove file in the storage and table
void deallocateFile(Storage *disk, FAT *fat, int i) {
    int aux;
    while(i != -1) {
        aux = fat[i].nextAddress;
        fat[i].block->fileID = 0;
        fat[i].block = NULL;
        free(fat[i].fileAddress);
        fat[i].fileAddress = NULL;
        fat[i].nextAddress = 0;
        disk->availableSpace++;
        i = aux;
    }
}