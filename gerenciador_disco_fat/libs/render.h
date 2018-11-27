#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "storage.h"

#define max(a, b) ((a)>(b) ? (a) : (b))

void printSequence(const char *str, int times);
void clearScreen();
void printHeader(const char *str);
void printStorageSpace(Storage *disk);
void printDetailedFileInfo(Node *node);
void printFileContent(Metadata *metadata, char name[]);
void printFileList(NodeList *list);
void printFiles(NodeList *list);
void printStorage(Storage *disk, unsigned storageSize);


#endif //DATA_STRUCTURE_RENDER_H
