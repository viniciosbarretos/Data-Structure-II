#ifndef SGBD_RENDER_H
#define SGBD_RENDER_H

#include "hashing.h"

#define r 100
#define c 120

void cleanBoard(char board[r][c], int row, int col);
void printBoard(char board[r][c], int row);
void renderFileDir(char board[r][c], int x, int y, int row, int col, Dir *dir);
void renderBucket(char board[r][c], int x, int y, int row, int col, int a, Bucket *bucket);
void renderArrow(char board[r][c], int x, int y, int row, int col, const char *trace);
void showHashTable(Dir *dir, Bucket *bucket);
#endif //SGBD_RENDER_H
