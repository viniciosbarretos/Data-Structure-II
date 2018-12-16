#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "render.h"
#include "hashing.h"

// Clear screen both windows and unix
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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
void renderFileDir(char board[r][c], int x, int y, int row, int col, Dir *dir) {
    int a=6, b=4;
    char aux[a][b];
    int i, j;

    //print globalDepth on aux board
    sprintf(aux[0], "+++");
    sprintf(aux[1], "+%d+", dir->globalDepth);
    sprintf(aux[2], "+++");

    a += 3;
    b -= 2;

    // Check if copy is possible.
    if (a+y <= row && b + x <= col) {
        // Copy for board.
        for (i=0; i<a; i++) {
            for (j=0; j<b; j++) {
                board[y+i][x+j] = aux[i][j];
            }
        }
    }

    for (int k = 0; k < pow(2,dir->globalDepth); k++) {
        //print dir on aux board
        sprintf(aux[0], "+-----+");
        sprintf(aux[1], "| %3d |", key);
        sprintf(aux[2], "+-----+");


        // Check if copy is possible.
        if (a+y <= row && b + x <= col) {
            // Copy for board.
            for (i=0; i<a; i++) {
                for (j=0; j<b; j++) {
                    board[y+i][x+j] = aux[i][j];
                }
            }
        }
        a += 3;
    }
}


void renderBucket(char board[r][c], int x, int y, int row, int col, int a, Bucket *bucket) {
    int b=26;
    char aux[a][b];
    int i, j;
    char k, z;

    // Print on aux board.
    sprintf(aux[0], "+Bucket %3d", key);
    sprintf(aux[1], "+--------------------+ +-+");
    sprintf(aux[2], "|%5d%5d%5d%5d| |%d|", bucket->items[0].id, bucket->items[1].id, bucket->items[2].id, bucket->items[3].id, bucket->localDepth);
    sprintf(aux[3], "+--------------------++-+ ");

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

void printSequence(const char *str, int times) {
    while ( times > 0 ) {
        printf("%s", str);
        times--;
    }
}

void showHashTable(Dir *dir, Bucket *bucket) {

    // Initiate control variables
    int a = 1;
    int aux = (int) pow(2,dir->globalDepth);
    int aux2 = (8 + 12*(dir->globalDepth-2));
    int count = 1;
    int x = 0;
    int y = 0;
    char trace[20];

    // Initiate the board.
    char board[r][c];
    cleanBoard(board, r, c);

    renderFileDir(board, x, y, r, c, dir);

    for (int i = 0; i < pow(2,dir->globalDepth); i++) {

        if (dir->key != NULL) {
            if (i < (pow(2,dir->globalDepth)/2)) {
                sprintf(trace, "R%d,U%d,R%d,", (4*count), aux, aux2-(4*count)); //generic functions to render the arrow
                renderArrow(board, x, y + 2, r, c, trace);
                count++; //control variables of functions
                aux -= 2;
                renderBucket(board, x, y, r, c, a, bucket);
                a +=5;
            } else {
                aux += 2; //control variables of functions
                count--;
                if () { //if 2 dirs point to the same bucket
                    sprintf(trace, "R%d,D%d,R3,U19,R%d", (4*count), aux, aux2-(4*count)-2); //generic functions to render the arrow
                    renderArrow(board, x, y + 2, r, c, trace);
                } else {
                    sprintf(trace, "R%d,U%d,R%d,", (4*count), aux, aux2-(4*count)); //generic functions to render the arrow
                    renderArrow(board, x, y + 2, r, c, trace);
                    renderBucket(board, x, y, r, c, a, bucket);
                }
                a +=5;
            }
        }
    }
    printBoard(board, (int) (pow(2,dir->globalDepth)*4+(pow(2,dir->globalDepth)-1)));//altura maxima dir->globalDepth)*4+(pow(2,dir->globalDepth)-1)
}