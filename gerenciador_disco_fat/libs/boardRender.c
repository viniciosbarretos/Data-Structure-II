#include "boardRender.h"
#include <stdio.h>
#include <string.h>
#include "storage.h"

#define lineStart '-'
#define lineH '-'
#define lineV '|'
#define lineJunction '+'
#define lineEnd '>'

typedef struct Trace {
    char direction;
    unsigned size;
} Trace;


void strcpyfrgm(char *buffer, const char *input, int start, int size) {
    int i;
    // if copy can be made.
    if ( (int) strlen(input) >= start+size) {
        // Copying all the chars
        for (i=0; i<size; i++) {
            buffer[i] = input[i+start];
        }
        // Add end to buffer.
        buffer[i] = '\0';
    }
}


int splitTrace(Trace traces[100], const char *string, char divider){
    int i=0, j=0, lenght=0, start=0;
    int n = (int) strlen(string);
    char aux[100];

    // Trace infos.
    char direction;
    int size;

    // Iterate over string finding the dividers.
    for(i=0; i<n; i++){
        if (string[i] == divider) {
            // Copy the fragment of trace.
            strcpyfrgm(aux, string, start, lenght);
            // Interpret and save the trace.
            sscanf(aux, "%c%d", &direction, &size);
            traces[j].direction = direction;
            traces[j].size = (unsigned) size;
            j++;
            // Reset markers.
            lenght = 0;
            start=i+1;
        }

        lenght++;
    }

    return j;
}


void zeroFill(char board[r][c], int row, int col) {
    int i, j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            board[i][j] = ' ';
        }
    }
}


void printBoard(char board[r][c], int row) {
    int i;

    for (i=0; i<row; i++) {
        printf("%s\n", board[i]);
    }

}


void renderFatNode(char board[r][c], int x, int y, int row, int col, FAT *fat) {
    int a=4, b=13;
    char aux[a][b];
    int i, j;

    // Print on aux board.
    sprintf(aux[0], "+-----------+");
    sprintf(aux[1], "| id:   %3d |", fat->block->logicalAddress);
    sprintf(aux[2], "| next: %3d |", fat->nextAddress);
    sprintf(aux[3], "+-----------+");

    // Check if copy is possible.
    if (a+y <= row && b + x <= col) {
        // Copy for board.
        for (i=0; i<a; i++) {
            for (j=0; j<b; j++) {
                board[y+i][x+j] = aux[i][j];
            }
        }
    }
}


void renderFileNode(char board[r][c], int x, int y, int row, int col, File *file) {
    int a=5, b=30;
    char aux[a][b];
    int i, j;

    // Print on aux board.
    sprintf(aux[0], "+----------------------------+");
    sprintf(aux[1], "| id:   %3d                  |", file->id);
    sprintf(aux[2], "| name: %-20s |", file->name);
    sprintf(aux[3], "| size: %3d                  |", file->size);
    sprintf(aux[4], "+----------------------------+");

    // Check if copy is possible.
    if (a+y <= row && b + x <= col) {
        // Copy for board.
        for (i=0; i<a; i++) {
            for (j=0; j<b; j++) {
                board[y+i][x+j] = aux[i][j];
            }
        }
    }
}


void renderArrow(char board[r][c], int x, int y, int row, int col, const char *trace) {
    int traceCount;
    Trace traces[50];
    char t = lineStart;
    // Decompose the trace.
    traceCount = splitTrace(traces, trace, ',');

    // Render the start line
    board[y][x] = t;
    traces[0].size--;

    // Render the trace.
    for (int i=0; i<traceCount; i++) {
        for (int j=0; j<traces[i].size; j++) {
            // Go to next position.
            switch (traces[i].direction) {
                case 'R': x++; t=lineH; break;
                case 'L': x--; t=lineH; break;
                case 'D': y++; t=lineV; break;
                case 'U': y--; t=lineV; break;
                default:break;
            }

            // Check for junction.
            if (j == traces[i].size-1) {
                if (i != traceCount-1) {
                    t = lineJunction;
                } else {
                    t = lineEnd;
                }
            }

            // Render point on board.
            board[y][x] = t;
        }
    }
}


void cleanBoard(char board[r][c], int row, int col) {
    int i;

    // Clean possible garbage on the board.
    zeroFill(board, row, col);

    // Add constraints to the borders.
    for (i=0; i<row; i++) {
        board[i][col-1] = '\0';
    }
}