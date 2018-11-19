#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "storage.h"


// This is like a disk formatting and mount
Storage* initializeStorage(unsigned size) {
    // Creates the storage and all its positions.
    Storage *storage = (Storage *) malloc (sizeof(Storage));   // Allocate the storage object.
    storage->data = malloc (sizeof(StorageBlock) * size);     // Allocate all positions.
    storage->availableSpace = size;                          // Set the total storage size.

    // Clears all storage positions.
    for (unsigned i = 0; i<size; i++) {
        storage->data[i].fileID = 0;
        storage->data[i].logicalAddress = i;
    }

    return storage;
}


// Initialize the table creating an array of FAT structure.
// Each position of array represents a table row with direct access.
FAT* initializeTable(unsigned storageSize) {
    // Allocate the Fat table on memory.
    FAT *fat = malloc (sizeof(FAT) * storageSize);

    // Clears all FAT positions.
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
    int prevAddress = - 1;

    // i<storageSize don't is checked because this code
    // will only execute if storage have available space

    // Add blocks for first available position.
    while (blockAdded<size) {
        if (fat[i].block == NULL) {
            // Save information in the disk and in the table.
            disk->data[i].fileID = id;
            fat[i].block = &disk->data[i];
            fat[i].nextAddress = -1;

            if (!blockAdded) {
                first = i;
            } else {
                fat[prevAddress].nextAddress = i;
            }

            // Update flags.
            prevAddress = i;
            blockAdded++;
            disk->availableSpace--;
        }
        i++;
    }

    // Return the position that files start on table
    return first;
}


// Create file content and call createData function to insert it into storage
void allocateFile(Storage *disk, FAT *fat, char *name, char *content, unsigned size, unsigned id) {
    // Allocate file node on memory
    File *newFile = malloc( sizeof(File) );

//Not working
//    struct tm * Date;
//    time_t Time;
//    time( &Time );
//    Date = gmtime( &Time );

    // Save information on file.
    strcpy(newFile->name, name);
    strcpy(newFile->content, content);
    newFile->id = id;
    newFile->size = size;
//    newFile->creationTime = Date->tm_sec;

    // Allocate file on disk.
    newFile->fatStartPosition = createData(disk, fat, size, newFile->id);
    // Save file pointer on its first entry on fat table.
    fat[newFile->fatStartPosition].fileAddress = newFile;
}


// Remove file in the storage and table
void deallocateFile(Storage *disk, FAT *fat, int i) {
    int next;

    // Delete file
    free(fat[i].fileAddress);

    // While isn't the last portion of table, clean it.
    while(i != -1) {
        next = fat[i].nextAddress;
        // Remove references from disk.
        fat[i].block->fileID = 0;
        fat[i].block = NULL;

        // Remove references from table.
        fat[i].fileAddress = NULL;
        fat[i].nextAddress = 0;

        // Increase disk space.
        disk->availableSpace++;

        // Go to next portion of file.
        i = next;
    }
}