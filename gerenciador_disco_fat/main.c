//
//  Laboratory of Data Structure II
//  David Candelero
//  Thiago Leal
//  Vinicios Barretos
//  Vinicius Martins
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render.h"
#include "storage.h"

// Clean buffer after a text input
void cleanBuffer() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}

// Options in main menu
void printOptions() {
    clearScreen();
    printf("\n0 -> End Simulation\n");
    printf("1 -> Create File\n");
    printf("2 -> Open File\n");
    printf("3 -> Delete File\n");
    printf("4 -> Show Storage\n");
    printf("5 -> Show Table\n");
    printf("6 -> Show Storage, Table and Files\n");
    printf("7 -> Show Available Storage Space \n");

    printf("Select your option: ");
}

// Request to user the informations to create a file
void createFile(Storage *disk, FAT *fat, unsigned id) {
    clearScreen();
    printf("[ Create File ]\n\n");
    char name[20], content[200];
    unsigned size;
    printf("File name: ");
    scanf("%s", name);
    cleanBuffer();
    printf("Content: ");
    scanf("%[^\n]", content);
    cleanBuffer();
    size = fileSize(content);
    if (size <= disk->availableSpace) { // Checks if there is available space at storage
        allocateFile(disk, fat, name, content, size, id);
        printf("\n------------------------------\n");
        printf("-  File Created Succesfully  -");
        printf("\n------------------------------\n");
        printf(" - Name: %s\n", name);
        printf(" - Size: %dw\n", size);
    }
    else {
        printf("\n-------------------------------------------\n");
        printf("- There is no Space to add file. Sorry :( -");
        printf("\n-------------------------------------------\n");
    }
}

// Ask to user what file will be deleted
void removeFile(Storage *disk, FAT *fat, unsigned storageSize) {
    int removeID, i;
    clearScreen();
    printf("[ Remove File ]\n\n");
    printFiles(fat, storageSize);
    printf("\nID of file you want to remove: ");
    scanf("%d", &removeID);
    cleanBuffer();
    for(i=0; i<storageSize; i++)
        if(fat[i].fileAddress != NULL)
            if(fat[i].fileAddress->id == removeID) {
                deallocateFile(disk, fat, i);
                printf("\n-------------------------------\n");
                printf("-       File %3d removed      -", removeID);
                printf("\n-------------------------------\n");
                removeID = -1; // Control variable
            }
    if(removeID != -1) {
        printf("\n-------------------------------\n");
        printf("-     File does not exist     -");
        printf("\n-------------------------------\n");
    }
}

int main() {
    unsigned option;
    unsigned storageSize = 300;
    unsigned id = 1;

    // Initialization of a 300w disk
    Storage *disk = initializeStorage(storageSize);

    // File Allocation Table
    FAT *fat = initializeTable(storageSize);

    do {
        printOptions();
        scanf("%d", &option);
        cleanBuffer();
        switch (option) {
            case 1:
                createFile(disk, fat, id++);
                break;

            case 2:
                break;
            case 3:
                removeFile(disk, fat, storageSize);
                break;
            case 4:
                printStorage(disk, storageSize);
                break;
            case 5:
                printTable(fat, storageSize);
                break;
            case 6:
                printFiles(fat, storageSize);
                break;
            case 7:
                printStorageSpace(disk);
                break;
            default:
                printf("Invalid Option! Try again.");
        }
        printf("\n\nPress enter to continue... ");
        getchar();
    } while(option);
    
    return 0;
}
