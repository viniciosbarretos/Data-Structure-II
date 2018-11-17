#include <stdio.h>
#include <stdlib.h>
#include "render.h"
#include "storage.h"

// Clear screen both windows and unix
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Print available storage space
void printStorageSpace(Storage *disk) {
    printf("\n--------------------------------\n");
    printf("-  Disk Available Space: %3dw  -", disk->availableSpace);
    printf("\n--------------------------------\n");
}

// Print all information of a file
void printFileInfo(File *file) {
    printf("\nName: %s\n", file->name);
    printf("ID: %d\n", file->id);
    printf("Size: %d\n", file->size);
    printf("Content: %s\n", file->content);
    printf("Data Start on Table: %d\n", file->fatStartPosition);
}

// Print a list of all files allocated at table and storage
void printFileList(FAT *fat, unsigned storageSize) {
    unsigned i;
    for(i=0; i<storageSize; i++) {
        if(fat[i].fileAddress != NULL)
            printf("ID: %d, Name: %s\n", fat[i].fileAddress->id, fat[i].fileAddress->name);
    }
}

// Print detailed all files allocated at table and storage
void printFiles(FAT *fat, unsigned storageSize) {
    unsigned i;
    for(i=0; i<storageSize; i++) {
        if(fat[i].fileAddress != NULL)
            printFileInfo(fat[i].fileAddress);
    }
}

// Print current table status in a matrix format
void printTable(FAT *fat, unsigned storageSize) {
    unsigned i, j=0;
    clearScreen();
    printf("[ Table Status ]\n\n");
    for (i=0; i<storageSize; i++) {
        printf("%4d", fat[i].nextAddress);
        j++;
        if(j == 30) {
            printf("\n");
            j = 0;
        }
    }
}

// Print current storage status in a matrix format
void printStorage(Storage *disk, unsigned storageSize) {
    unsigned i, j=0;
    clearScreen();
    printf("[ SSD Status ]\n\n");
    for (i=0; i<storageSize; i++) {
        if(disk->data[i].fileID == 0)
            printf("   -");
        else
            printf("%4d", disk->data[i].fileID);
        j++;
        if(j == 30) {
            printf("\n");
            j = 0;
        }
    }
}