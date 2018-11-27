#ifndef DATA_STRUCTURE_PERSIST_H
#define DATA_STRUCTURE_PERSIST_H

#include "storage.h"

void dehydrate(Storage *storage, NodeList *nodeList, int storageSize);
void hydrate(Storage **pStorage, NodeList **pNodeList, int storageSize);

#endif //DATA_STRUCTURE_PERSIST_H
