#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "render.h"
#include "storage.h"
#include "boardRender.h"

// Clear screen both windows and unix
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printSequence(const char *str, int times) {
    while( times > 0 ) {
        printf("%s", str);
        times--;
    }
}

void printHeader(const char *str) {
    unsigned size = (unsigned) strlen(str);
    printf("\n");
    printSequence("-", size + 8);
    printf("\n-   %s   -\n", str);
    printSequence("-", size + 8);
    printf("\n");
}

// Print available storage space
void printStorageSpace(Storage *disk) {
    printf("\n--------------------------------\n");
    printf("-  Disk Available Space: %3dw  -", disk->availableSpace);
    printf("\n--------------------------------\n");
}

// Print all information of a file
void printDetailedFileInfo(FAT *fat, File *file) {
    // Initiate control variables
    int x = 0;
    int y = 0;
    int lines = 0;
    char trace[20];
    int isFirstArrow = 1;

    // Initiate the board.
    char board[r][c];
    cleanBoard(board, r, c);

    // Render file info's.
    renderFileNode(board, x, y, r, c, file);
    x+=30;
    lines +=5;

    // Render first arrow.
    renderArrow(board, x, y+2, r, c, "R3,");

    // Iterate over pointer ons FAT's table.
    int aux = file->fatStartPosition;
    while (aux != -1) {
        if (x + 16 < c) {
            if (!isFirstArrow) {
                renderArrow(board, x, y+2, r, c, "R3,");
            } else {
                isFirstArrow = 0;
            }
            renderFatNode(board, x+3, y, r, c, &fat[aux]);
            x+=16;
            aux = fat[aux].nextAddress;
        } else {
            sprintf(trace, "R3,D2,L%d,D3,R1,", x-29);
            renderArrow(board, x, y+2, r, c, trace);
            y += 5;
            x = 30;
            renderFatNode(board, x+3, y, r, c, &fat[aux]);
            isFirstArrow=1;
            lines += 5;
        }
    }

    printBoard(board, lines);
}


void printFileContent(File *file) {
    printSequence("-", 80);
    printf("\nName: \n%s\n", file->name);
    printf("\nContent: \n%s\n", file->content);
    printSequence("-", 80);
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
        if(fat[i].fileAddress != NULL) {
            printDetailedFileInfo(fat, fat[i].fileAddress);
        }
    }
}


// Print current table status in a matrix format
void printTable(FAT *fat, unsigned storageSize) {
    unsigned i, j=0;

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