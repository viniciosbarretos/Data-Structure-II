#ifndef DATA_STRUCTURE_BOARDRENDER_H
#define DATA_STRUCTURE_BOARDRENDER_H

#include "storage.h"

#define r 100
#define c 120

void cleanBoard(char board[r][c], int row, int col);
void printBoard(char board[r][c], int row);
void renderFileNode(char board[r][c], int x, int y, int row, int col, Node *node);
void renderMetadata(char board[r][c], int x, int y, int row, int col, Metadata *info);
void renderArrow(char board[r][c], int x, int y, int row, int col, const char *trace);



#endif //DATA_STRUCTURE_BOARDRENDER_H
