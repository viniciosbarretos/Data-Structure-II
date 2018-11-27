#include "persist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

/*
 * storage.txt
 * ---------------------------------------------------
 * // Storage                             // Node list.
 * 1;1;1;1;1;1;2;2;2;5;5;4;4;4;4;5;5;5;5; 0;{metadata};1;{node};1;{node};0;{metadata};1;{node};0;{metadata};1{node};
 */

/*
 * Dehydrate the storage data.
 * */
//Saving StorageState in a real file storage.txt
void dehydrateStorage(FILE *file, Storage *storage, int storageSize) {
    // Iterate over the storage and save in file.
    for (int i = 0; i < storageSize; i++) {
        fprintf(file, "%d;", storage->data[i].fileID);
    }
}

void dehydrateNodeList(FILE *file, NodeList *nodeList) {
    // Control variables
    Node *aux = nodeList->start;
    int id = -1;

    // Iterate over the list and save in file.
    while (aux) {
        if (aux->metadata->id == id) {
            // Nodes information - 1: Start of a node.
            fprintf(file, "1;%d,%d;", aux->startPosition, aux->size);
            aux = aux->next;
        }
        else {
            // Metadata information - 0: Start of a metadata.
            fprintf(file, "0;%s,%d,%d,%d;", aux->metadata->name, aux->metadata->size, aux->metadata->id, aux->metadata->creationTime);
            id = aux->metadata->id;
        }
    }
}

void dehydrate(Storage *storage, NodeList *nodeList, int storageSize) {
    FILE *file = fopen("storage.txt", "w");

    dehydrateStorage(file, storage, storageSize);
    dehydrateNodeList(file, nodeList);

    fclose(file);
}

/*
 * Hydrate the storage data.
 */
Storage* hydrateStorage(FILE *file, int size) {
    // Creates the storage and all its positions.
    Storage *storage = (Storage *) malloc (sizeof(Storage));   // Allocate the storage object.
    storage->data = malloc (sizeof(StorageBlock) * size);     // Allocate all positions.
    storage->availableSpace = (unsigned int) size;           // Set the total storage size.

    // Restore the id for all storage positions.
    for (unsigned i = 0; i<size; i++) {
        fscanf(file, "%d;", &storage->data[i].fileID);
        storage->data[i].logicalAddress = i;
    }

    return storage;
}

NodeList* hydrateNodeList(FILE *file) {
    // Starting an empty list.
    NodeList *list = newNodeList();

    // Start some control variables.
    Node *aux;
    Metadata *metaTemp = NULL;
    char buffer[200];
    int identifier;

    // Iterate over the list.
    while (!feof(file)) {
        // Read the identifier.
        fscanf(file, "%d;", &identifier);

        if (identifier) { // Save the node in the list.
            // Allocate memory for the node.
            aux = (Node*) malloc(sizeof(Node));

            // Read the node.
            fscanf(file, "%d,%d;", &aux->startPosition, &aux->size);

            // Point to metadata.
            aux->metadata = metaTemp;

            // Add on list.
            list = nodeListInsertEnd(list, aux);
        }
        else { // Get the metadata and save then temporary.
            // Allocate memory for the metadata.
            metaTemp = (Metadata*) malloc(sizeof(Metadata));

            // Read the metadata.
            fscanf(file, "%[^,],%d,%d,%d;", buffer, &metaTemp->size, &metaTemp->id, &metaTemp->creationTime);

            // Allocate the right memory needed for the name.
            metaTemp->name = malloc( sizeof(char) * (strlen(buffer) + 1) );

            // Copy the file name from buffer to metadata.
            strcpy(metaTemp->name, buffer);
        }
    }

    return list;
}

void hydrate(Storage **pStorage, NodeList **pNodeList, int storageSize) {
    FILE *file = fopen("storage.txt", "r");

    // If file can be opened, rehydrate him.
    if (file) {
        *pStorage = hydrateStorage(file, storageSize);
        *pNodeList = hydrateNodeList(file);
    } else { // Else, initialize a new one.
        *pStorage = initializeStorage((unsigned int) storageSize);
        *pNodeList = newNodeList();
    }

    fclose(file);
}