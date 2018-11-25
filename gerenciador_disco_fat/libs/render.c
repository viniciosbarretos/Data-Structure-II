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
    while ( times > 0 ) {
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
void printDetailedFileInfo(Node *node) {
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
    renderMetadata(board, x, y, r, c, node->metadata);
    x+=30;
    lines +=5;

    // Render first arrow.
    renderArrow(board, x, y+2, r, c, "R3,");

    // Iterate over pointer ons FAT's table.
    Node *aux = node;
    while (aux && aux->metadata->id == node->metadata->id) {
        if (x + 16 < c) {
            if (!isFirstArrow) {
                renderArrow(board, x, y+2, r, c, "R3,");
            } else {
                isFirstArrow = 0;
            }
            renderFileNode(board, x + 3, y, r, c, aux);
            x+=16;
        } else {
            sprintf(trace, "R3,D2,L%d,D3,R1,", x-29);
            renderArrow(board, x, y+2, r, c, trace);
            y += 5;
            x = 30;
            renderFileNode(board, x + 3, y, r, c, aux);
            isFirstArrow=1;
            lines += 5;
        }
        aux = aux->next;
    }

    printBoard(board, max(6, lines));
}


void printFileContent(Metadata *metadata) {
    printSequence("-", 80);
    printf("\nName: \n%s\n", metadata->name);
    printf("\nContent: \n%s\n", "test content");
    printSequence("-", 80);
}


// Print a list of all files allocated at table and storage
void printFileList(NodeList *list) {
    int oldId = -1;
    int id;

    // Iterate over list
    Node *aux = list->start;
    while (aux) {
        id = aux->metadata->id;
        if (oldId != id) {
            oldId = id;
            printf("ID: %d, Name: %s\n", id, aux->metadata->name);
        }

        aux = aux->next;
    }
}


// Print detailed all files allocated at table and storage
void printFiles(NodeList *list) {
    int oldId = -1;
    int id;

    // Iterate over list
    Node *aux = list->start;
    while (aux) {
        id = aux->metadata->id;
        if (oldId != id) {
            oldId = id;
            printDetailedFileInfo(aux);
        }
        aux = aux->next;
    }
}


// Print current table status in a matrix format
/*
void printTable(FAT *fat, unsigned storageSize) {
    unsigned i, j=0;

    for (i=0; i<storageSize; i++) {
        if (fat[i].nextAddress == 0)
            printf("   -");
        else
            printf("%4d", fat[i].nextAddress);
        j++;
        if (j == 30) {
            printf("\n");
            j = 0;
        }
    }
}
*/

// Print current storage status in a matrix format
void printStorage(Storage *disk, unsigned storageSize) {
    unsigned i, j=0;

    for (i=0; i<storageSize; i++) {
        if (disk->data[i].fileID == 0)
            printf("   -");
        else
            printf("%4d", disk->data[i].fileID);
        j++;
        if (j == 30) {
            printf("\n");
            j = 0;
        }
    }
}