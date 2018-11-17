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

// Universal variables
//unsigned id = 1;
//unsigned storageSize = 300;

// Clear screen both windows and unix
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Clean buffer after a text input
void cleanBuffer() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}

// Each block have 1w size and a logical address
typedef struct StorageBlock {
    unsigned fileID;
    unsigned logicalAddress;
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
    StorageBlock *block; // Logical address of storage block
    File *fileAddress; // Point to file address
    int nextAddress; // Next fat address of a file
} FAT;

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

// Count file size based at amount of character typed
unsigned fileSize(char *content) {
    unsigned size = (unsigned) strlen(content);
    if(size + 2 <= 20)
        return size + 2;
    else
        return 20;
}

// Insert data into storage and reference in table
unsigned createData(Storage *disk, FAT *fat, unsigned size, unsigned id) {
    unsigned blockAdded = 0, i = 0, first=0;
    int aux = - 1;
    
    // i<storageSize dont is checked because this code
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
    printf("7 -> Show Available Storage Space ");
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

void printFileList(FAT *fat, unsigned storageSize) {
    unsigned i;
    for(i=0; i<storageSize; i++) {
        if(fat[i].fileAddress != NULL)
            printf("ID: %d, Name: %s\n", fat[i].fileAddress->id, fat[i].fileAddress->name);
    }
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

// Print all files allocated at table and storage
void printFiles(FAT *fat, unsigned storageSize) {
    unsigned i;
    for(i=0; i<storageSize; i++) {
        if(fat[i].fileAddress != NULL)
            printFileInfo(fat[i].fileAddress);
    }
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
        }
        printf("\n\nPress enter to continue... ");
        getchar();
    } while(option);
    
    return 0;
}
