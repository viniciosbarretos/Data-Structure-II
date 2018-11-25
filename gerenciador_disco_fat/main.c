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
#include "libs/render.h"
#include "libs/storage.h"

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

// Request the information to create a file
void createFile(Storage *disk, NodeList **files, unsigned diskSize, unsigned id) {
    char name[20], content[200];
    unsigned size;

    clearScreen();
    printf("[ Create File ]\n");
    printf(" > File name: ");
    scanf("%[^\n]", name);
    cleanBuffer();

    printf(" > Content: ");
    scanf("%[^\n]", content);
    cleanBuffer();

    size = fileSize(content);
    // Checks if there is available space on storage.
    if (size <= disk->availableSpace) {

        //Creating command to move file for Files directory
        char command[100];
        strcpy(command, "mv " );
        strcat(command, name);
        strcat(command, "\t");
        strcat(command, " files");

        //Creating real file in disk
        FILE *file;
        file = fopen(name, "w");
        fprintf(file, "%s", content);
        fclose(file);

        //Moving created file to directory Files
        system(command); //Only for linux

        allocateFile(disk, files, diskSize, id, name, content, size);
        printHeader("File created successfully");
        printf(" - Name: %s\n", name);

        printf(" - Size: %dw\n", size);
    }
    else {
        printHeader("Not enough space to add file. Sorry ;-;");
    }
}

// Ask to user what file will be deleted
void removeFile(Storage *storage, NodeList **files) {
    unsigned removeID;
    char option;
    clearScreen();

    printf("[ Files on storage ]\n");
    printFileList(*files);

    printf("\n[ Remove a file ]\n");
    printf(" > File id: ");
    scanf("%d", &removeID);
    cleanBuffer();

    printf("\nFile %d will be removed. Are you sure? [y/n]: ", removeID);
    scanf("%c", &option);

    // Check with user really agree with that.
    if (option == 'y' || option == 'Y') {
        cleanBuffer();

        removeID = (unsigned) deallocateFile(storage, files, removeID);

//        for (i=0; i<storageSize; i++) {
//            if (fat[i].fileAddress != NULL) {
//                if (fat[i].fileAddress->id == removeID) {
//
//                    //Accessing files directory for remove successful
//                    char dir[50];
//                    strcpy(dir, "files/");
//                    strcat(dir, fat[i].fileAddress->name);
//
//                    //Removing real file from directory 'Files'.
//                    FILE *file;
//                    file = fopen(dir, "r");
//                    fclose(file);
//                    remove(dir);
//
//                    deallocateFile(disk, fat, i);
//                    // Delete file
//                    free(fat[i].fileAddress);
//                    printHeader("File removed successfully");
//                    removeID = 0; // Control variable
//                }
//            }
//        }
        if (removeID == 0) {
            printHeader("File does not exist");
        }
    }
    else {
        printHeader("Removal canceled");
    }

}

void showFile(NodeList *files) {
    unsigned i, id, found = 0;
    clearScreen();

    printf("[ Files on storage ]\n");
    printFileList(files);

    printf("\n[ Select a file to open ]\n");
    printf(" > File id: ");
    scanf("%d", &id);
    cleanBuffer();

    // Search for file on table.
    Node *aux = files->start;
    while (aux && !found) {
        if (aux->metadata->id == id) {
            printFileContent(aux->metadata);
            found = 1;
        }
        aux = aux->next;
    }

    if (!found) {
        printHeader("File does not exist");
    }
}

int main() {
    unsigned option;
    unsigned storageSize = 300;
    unsigned id = 1;

    // Initialization of a 300w disk
    Storage *disk = initializeStorage(storageSize);

    // Initialize Node list
    NodeList *files = newNodeList();

    // Create files folder
    system("mkdir files");

    // automated test.
    allocateFile(disk, &files, storageSize, id++, "amor", "asdfasdfasdf", 3);
    allocateFile(disk, &files, storageSize, id++, "Belinha", "asdfasdfasdf", 3);
    allocateFile(disk, &files, storageSize, id++, "coracao", "asdfasdfasdf", 3);
    allocateFile(disk, &files, storageSize, id++, "dedo", "asdfasdfasdf", 3);
    deallocateFile(disk, &files, 1);
    deallocateFile(disk, &files, 3);

    do {
        printOptions();
        scanf("%d", &option);
        cleanBuffer();
        switch (option) {
            case 0:
                printf("\n\nBye bye :)\n");
//                if(disk->availableSpace < storageSize) // Checks if there are files
//                    system("rm files/*"); // Clear files folder
                break;
            case 1:
                createFile(disk, &files, storageSize, id++);
                break;
            case 2:
                if(disk->availableSpace < storageSize)
                    showFile(files);
                else {
                    clearScreen();
                    printf("\n[ There is no file to be shown ]\n");
                }
                break;
            case 3:
                if(disk->availableSpace < storageSize)
                    removeFile(disk, &files);
                else {
                    clearScreen();
                    printf("\n[ There is no file to be deleted ]\n");
                }
                break;
            case 4:
                printf("\n[ Storage ]\n\n");
                printStorage(disk, storageSize);
                break;
            case 5:
                printf("\n[ Files in disk ]\n\n");
                printFileList(files);
                break;
            case 6:
                printf("\n[ Storage ]\n\n");
                printStorage(disk, storageSize);

                printf("\n\n[ Files ]\n");
                printFiles(files);
                break;
            case 7:
                printStorageSpace(disk);
                break;
            default:
                printf("Invalid Option! Try again.");
        }
        printf("\n\nPress enter to continue... ");
        getchar();
    } while (option);
    
    return 0;
}
