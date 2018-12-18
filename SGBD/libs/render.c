#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "customer.h"
#include "render.h"
#include "hashing.h"
#include "utils.h"

// Clear screen both windows and unix
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

typedef struct Line {
    char lineStart;
    char lineH;
    char lineV;
    char lineJunction;
    char lineEnd;
} Line;

typedef struct Blackboard {
    int width;
    int height;
    char **area;
} Blackboard;

typedef struct Trace {
    char direction;
    unsigned size;
} Trace;

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

void printCostumer(Customer customer) {
    printf("+");
    printSequence("-", 32);
    printf("+\n");
    printf("| id:   %24d |\n", customer.id);
    printf("| Name: %24s |\n", customer.name);
    printf("| Type: %23s%c |\n", "", customer.type);
    printf("| Balance: %21.2f |\n", customer.overbalance);
    printf("+");
    printSequence("-", 32);
    printf("+\n");
}

// Split line trace string on a vector of Trace.
int splitTrace(Trace traces[100], const char *string, char divider){
    int i=0, j=0, length=0, start=0;
    int n = (int) strlen(string);
    char aux[100];

    // Trace infos.
    char direction;
    int size;

    // Iterate over string finding the dividers.
    for (i=0; i<n; i++){
        if (string[i] == divider) {
            // Copy the fragment of trace.
            strCopyFragment(aux, string, start, length);
            // Interpret and save the trace.
            sscanf(aux, "%c%d", &direction, &size);
            traces[j].direction = direction;
            traces[j].size = (unsigned) size;
            j++;
            // Reset markers.
            length = 0;
            start=i+1;
        }

        length++;
    }

    return j;
}

// Creates a new blackboard.
Blackboard newBlackboard(int width, int height) {
    int i;

    // Initialize blackboard values.
    Blackboard bb;
    bb.width = width;
    bb.height = height;

    // Alloc memory for area.
    bb.area = malloc(sizeof(char *) * height);
    for (i=0; i < height; i++) {
        bb.area[i] = malloc(sizeof(char) * width);
    }

    return bb;
}

// Clean the area of the blackboard.
void cleanBlackboard(Blackboard blackboard) {
    int i, j;

    for (i = 0; i < blackboard.height; i++) {
        for (j = 0; j < blackboard.width; j++) {
            blackboard.area[i][j] = ' ';
        }
    }
}

void startBlackboard(Blackboard blackboard) {
    int i;

    // Clean possible garbage on the board.
    cleanBlackboard(blackboard);

    // Add constraints to the borders.
    for (i = 0; i < blackboard.height; i++) {
        blackboard.area[i][blackboard.width-1] = '\0';
    }
}

// Copy the content from one blackboard to another.
void copyBetweenBlackboards(Blackboard from, Blackboard to, int x, int y) {
    int i, j;

    // Check if copy is possible.
    if (from.height+y <= to.height && from.width + x <= to.width) {

        // Copy for board.
        for (i = 0; i < from.height; i++) {
            for (j = 0; j < from.width; j++) {
                to.area[y+i][x+j] = from.area[i][j];
            }
        }
    }
}

// Print the content of the blackboard on terminal.
void printBlackboard(Blackboard blackboard, int maxHeight) {
    int i;

    for (i = 0; i < maxHeight; i++) {
        printf("%s\n", blackboard.area[i]);
    }

}

// Render a arrow line on the blackboard.
void renderArrow(Blackboard blackboard, int x, int y, const char *trace, Line line) {
    int traceCount, i, j;
    char t = line.lineStart;
    Trace traces[50];

    // Decompose the trace.
    traceCount = splitTrace(traces, trace, ',');

    // Render the first line part.
    blackboard.area[y][x] = t;
    traces[0].size--;

    // Render the arrow, part after part.
    for (i=0; i<traceCount; i++) {
        for (j=0; j<traces[i].size; j++) {
            // Go to next position.
            switch (traces[i].direction) {
                case 'R': x++; t=line.lineH; break;
                case 'L': x--; t=line.lineH; break;
                case 'D': y++; t=line.lineV; break;
                case 'U': y--; t=line.lineV; break;
                default: break;
            }

            // Check if its a junction.
            if (j == traces[i].size-1) {
                if (i != traceCount-1) {
                    t = line.lineJunction;
                } else {
                    t = line.lineEnd;
                }
            }

            // Render part on board with non destruction.
            if (blackboard.area[y][x] == ' ') {
                blackboard.area[y][x] = t;
            }
        }
    }
}

// Render the SGBD hash directory in the blackboard.
void renderFileDir(Blackboard blackboard, int x, int y, Dir *dir) {
    int k, n;

    // Initialize board.
    Blackboard aux = newBlackboard(7, 3);
    cleanBlackboard(aux);

    // Calc the height of the dir.
    n = (int) floor(pow(2, dir->globalDepth));

    // Print global depth on aux board.
    sprintf(aux.area[0], "+---+  ");
    sprintf(aux.area[1], "| %d |  ", dir->globalDepth);
    sprintf(aux.area[2], "+---+  ");

    // Copy for board.
    copyBetweenBlackboards(aux, blackboard, x, y);

    // Change insertion point.
    y += aux.height-1;

    // Render dir nodes.
    for (k = 0; k < n; k++) {
        // Print dir on aux board.
        sprintf(aux.area[0], "+-----+");
        sprintf(aux.area[1], "| %3d |", k);
        sprintf(aux.area[2], "+-----+");

        // Copy for board.
        copyBetweenBlackboards(aux, blackboard, x, y);

        // Change insertion point.
        y += aux.height-1;
    }
}

void renderBucket(Blackboard blackboard, int x, int y, Bucket *bucket, int name) {
    Blackboard aux = newBlackboard(26, 5);

    // Print on aux board.
    sprintf(aux.area[0], "Bucket %3d                ", name);
    sprintf(aux.area[1], "+---------------------++-+");
    sprintf(aux.area[2], "| %4d %4d %4d %4d ||%d|", bucket->items[0].id, bucket->items[1].id, bucket->items[2].id, bucket->items[3].id, bucket->localDepth);
    sprintf(aux.area[3], "| %4d %4d %4d %4d |+-+", bucket->items[0].line, bucket->items[1].line, bucket->items[2].line, bucket->items[3].line);
    sprintf(aux.area[4], "+---------------------+   ");

    // Copy for board
    copyBetweenBlackboards(aux, blackboard, x, y);
}

void printConnectorArrow(Blackboard blackboard, int x, int y, int xEnd, int yEnd, int dist, Line line) {
    char trace[20];
    char direction;

    if (y - yEnd > 0) {
        direction = 'U';
    } else {
        direction = 'D';
    }

    sprintf(trace, "R%d,%c%d,R%d,", dist, direction, abs(y - yEnd), xEnd-x-dist);
    renderArrow(blackboard, x, y, trace, line);
}

void printConnectorAroundArrow(Blackboard blackboard, int x, int y, int xEnd, int yEnd, int dist, int depth, Line line) {
    char trace[20];

    sprintf(trace, "R%d,D%d,R%d,U%d,L%d,", dist, depth - y + dist - 8, xEnd-x, depth - 8 + dist - yEnd, dist-2);
    renderArrow(blackboard, x, y, trace, line);
}

void renderHashTable(Dir *dir) {
    int i, x, y, n, dist, dirSize, yBucket, prev, depth;

    printHeader("Hash Directory");

    // Calc the height of the dir.
    n = (int) floor(pow(2, dir->globalDepth));

    // Initiate the board.
    Blackboard blackboard;
    blackboard = newBlackboard(120, 100);

    // Clean the blackboard area and set end flag characters.
    startBlackboard(blackboard);

    // Create the line type.
    Line line1 = {'-', '-', '|', '+', '>'};
    Line line2 = {'~', '~', ':', '*', '<'};

    // Get the number of different buckets in dir.
    dirSize = differentBucketsInDir(dir);

    // Calc the render position of dir.
    x = 0;
    y = ((dirSize * 6) - (dirSize * 2 + 6)) / 2;

    // Render the dir.
    renderFileDir(blackboard, x, y, dir);

    // Start control variables.
    depth = 0;
    yBucket = 0;
    y += 3;
    dist = 10;

    // Print the buckets
    for (i = 0; i < n; i++) {
        // Get the bucket previous position
        prev = bucketAppearsBefore(dir, i);

        // Check if connect to a new bucket or in a exist one.
        if (prev == -1) {
            // Render bucket and arrow.
            renderBucket(blackboard, 31, yBucket, dir->key[i], i);
            printConnectorArrow(blackboard, 7, y, 30, yBucket+2, dist, line1);

            // Increment yBucket counters.
            yBucket += 6;

        } else {
            printConnectorAroundArrow(blackboard, 7, y, 56, 6 * prev + 2, dist, dirSize * 6, line2);
            depth += 2;
        }

        // Alter dist.
        if (i + 1 < n / 2) { // If its the first half.
            dist += 3;
        } else if (i >= n / 2 || n != dirSize){ // if its the last half + 1.
            dist -= 3;
        }

        // Increase y counter.
        y += 2;
    }

    depth += yBucket;

    printBlackboard(blackboard, depth+3);
}