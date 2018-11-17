#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "storage.h"


void clearScreen();
void printStorageSpace(Storage *disk);
void printFileInfo(File *file);
void printFileList(FAT *fat, unsigned storageSize);
void printFiles(FAT *fat, unsigned storageSize);
void printTable(FAT *fat, unsigned storageSize);
void printStorage(Storage *disk, unsigned storageSize);


#endif //DATA_STRUCTURE_RENDER_H
