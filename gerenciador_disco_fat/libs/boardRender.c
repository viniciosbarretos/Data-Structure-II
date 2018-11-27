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

//typedef struct

// Clean a board.
void zeroFill(char board[r][c], int row, int col) {
    int i, j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            board[i][j] = ' ';
        }
    }
}


// Copy from input to buffer in a certain range.
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

// Split line trace string on a vector of Trace.
int splitTrace(Trace traces[100], const char *string, char divider){
    int i=0, j=0, lenght=0, start=0;
    int n = (int) strlen(string);
    char aux[100];

    // Trace infos.
    char direction;
    int size;

    // Iterate over string finding the dividers.
    for (i=0; i<n; i++){
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

// Render a arrow line.
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


//void copybetweenboards(char **buffer, char **input, int x, int y, );


// Render the file fragment node.
void renderFileNode(char board[r][c], int x, int y, int row, int col, Node *node) {
    int a=6, b=14;
    char aux[a][b];
    int i, j;

    // Print on aux board.
    sprintf(aux[0], "+------------+");
    sprintf(aux[1], "| id:    %3d |", node->metadata->id);
    sprintf(aux[2], "| start: %3d |", node->startPosition);
    sprintf(aux[3], "| size:  %3d |", node->size);
    sprintf(aux[4], "+------------+");

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


void renderMetadata(char board[r][c], int x, int y, int row, int col, Metadata *info) {
    int a=6, b=30;
    char aux[a][b];
    int i, j;
    char k, z;

    // Print on aux board.
    sprintf(aux[0], "+----------------------------+");
    sprintf(aux[1], "| id:   %3d                  |", info->id);
    sprintf(aux[2], "| name: %-20s |", info->name);
    sprintf(aux[3], "| size: %3d                  |", info->size);
    sprintf(aux[4], "| creation time: %10d  |", info->creationTime);
    sprintf(aux[5], "+----------------------------+");

    // Check if copy is possible.
    if (a+y <= row && b + x <= col) {
        // Copy for board.
        for (i=0; i<a; i++) {
            for (j=0; j<b; j++) {
                k = aux[i][j];
                z = board[y+i][x+j];
                board[y+i][x+j] = aux[i][j];
            }
        }
    }
}

void printBoard(char board[r][c], int row) {
    int i;

    for (i=0; i<row; i++) {
        printf("%s\n", board[i]);
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