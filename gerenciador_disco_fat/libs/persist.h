#ifndef DATA_STRUCTURE_PERSIST_H
#define DATA_STRUCTURE_PERSIST_H

#include "storage.h"

void dehydrate(Storage *storage, NodeList *nodeList, int id, int storageSize);
void hydrate(Storage **pStorage, NodeList **pNodeList, int *id, int storageSize);

#endif //DATA_STRUCTURE_PERSIST_H