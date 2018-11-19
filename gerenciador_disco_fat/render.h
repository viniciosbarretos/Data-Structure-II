#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "storage.h"

void clearScreen();
void printHeader(const char *str);
void printStorageSpace(Storage *disk);
void printFileInfo(FAT *fat, File *file);
void printFileList(FAT *fat, unsigned storageSize);
void printFiles(FAT *fat, unsigned storageSize);
void printTable(FAT *fat, unsigned storageSize);
void printStorage(Storage *disk, unsigned storageSize);


#endif //DATA_STRUCTURE_RENDER_H
