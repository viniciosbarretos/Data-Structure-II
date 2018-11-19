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
    printf("\n1 - Create File\n");
    printf("2 - Open File\n");
    printf("3 - Delete File\n");
    printf("4 - Show Storage\n");
    printf("5 - Show Table\n");
    printf("6 - Show Storage, Table and Files\n");
    printf("7 - Show Available Storage Space \n");
    printf("0 - End Simulation\n");

    printf("\nSelect your option: ");
}

// Request to user the information to create a file
void createFile(Storage *disk, FAT *fat, unsigned id) {
    char name[20], content[200];
    unsigned size;

    clearScreen();

    printf("[ Create File ]\n");
    printf(" > File name: ");
    scanf("%s", name);
    cleanBuffer();

    printf(" > Content: ");
    scanf("%[^\n]", content);
    cleanBuffer();

    size = fileSize(content);
    // Checks if there is available space on storage.
    if (size <= disk->availableSpace) {
        allocateFile(disk, fat, name, content, size, id);
        printHeader("File created successfully");
        printf(" - Name: %s\n", name);
        printf(" - Size: %dw\n", size);
    }
    else {
        printHeader("Not enough space to add file. Sorry ;-;");
    }
}

// Ask to user what file will be deleted
void removeFile(Storage *disk, FAT *fat, unsigned storageSize) {
    unsigned removeID, i;
    char option;
    clearScreen();

    printf("[ Files on storage ]\n");
    printFileList(fat, storageSize);

    printf("\n[ Remove a file ]\n");
    printf(" > File id: ");
    scanf("%d", &removeID);
    cleanBuffer();

    printf("\nFile %d will be removed. Are you sure? [y/n]: ", removeID);
    scanf("%c", &option);

    // Check with user really agree with that.
    if(option == 'y' || option == 'Y') {
        cleanBuffer();
        for(i=0; i<storageSize; i++) {
            if(fat[i].fileAddress != NULL) {
                if(fat[i].fileAddress->id == removeID) {
                    deallocateFile(disk, fat, i);
                    printHeader("File removed successfully");
                    removeID = 0; // Control variable
                }
            }
        }
        if(removeID != 0) {
            printHeader("File does not exist");
        }
    }
    else {
        printHeader("Removal canceled");
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
            case 0:
                printf("\n\nBye bye :)\n");
                break;
            case 1:
                createFile(disk, fat, id++);
                break;
            case 2:
                break;
            case 3:
                removeFile(disk, fat, storageSize);
                break;
            case 4:
                printf("\n[ Storage ]\n\n");
                printStorage(disk, storageSize);
                break;
            case 5:
                printf("\n\n[ Table ]\n\n");
                printTable(fat, storageSize);
                break;
            case 6:
                printf("\n[ Storage ]\n\n");
                printStorage(disk, storageSize);

                printf("\n\n[ Table ]\n\n");
                printTable(fat, storageSize);

                printf("\n\n[ Files ]\n");
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
