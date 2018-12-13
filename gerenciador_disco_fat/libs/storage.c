#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "storage.h"
#include "render.h"

// Count file size based at amount of character typed
unsigned fileSize(char *content) {
    unsigned size = (unsigned) (strlen(content) / 8 + 2);
    return (size < 20) ? size : 20;
}


// Create the node list.
NodeList *newNodeList() {
    NodeList *nodeList = (NodeList *) malloc(sizeof(NodeList));
    nodeList->start = NULL;
    nodeList->end = NULL;
    return nodeList;
}

// Insert an element at the end of the node's list
NodeList *nodeListInsertEnd(NodeList *nodeList, Node *node) {
    if (nodeList->start) { // Save when have a list
        node->next = NULL;
        nodeList->end->next = node;
        nodeList->end = node;
    }
    else { // Save when list is empty.
        node->next = NULL;
        nodeList->start = node;
        nodeList->end = node;
    }

    return nodeList;
}


// Format ans mount the disk
Storage* initializeStorage(unsigned size) {
    // Creates the storage and all its positions.
    Storage *storage = (Storage *) malloc (sizeof(Storage));   // Allocate the storage object.
    storage->data = malloc (sizeof(StorageBlock) * size);     // Allocate all positions.
    storage->availableSpace = size;                          // Set the total storage size.

    // Clears all storage positions.
    for (unsigned i = 0; i<size; i++) {
        storage->data[i].fileID = 0;
        storage->data[i].logicalAddress = i;
    }

    return storage;
}

// Save the file sequentially on disk by giving a start position and a size.
void saveOnDisk (Storage *storage, unsigned id, unsigned startPosition, unsigned size) {
    // Walks on disk saving the info.
    while (size > 0) {
        // Save part of the file to disk.
        storage->data[startPosition].fileID = id;
        // Increment counters.
        startPosition++;
        size --;
    }
}

char * getFileContent (char name[]) {
    FILE *file;

    char dir[50];
    strcpy(dir, "Files/");
    strcat(dir, name);

    file = fopen(dir, "r");
    char *content = malloc(sizeof(char)*200);

    if (file == NULL)
    {
        return "You have to close file first, to access content.";
    }
    else {
        fgets(content, 200, file);
        fclose(file);
        return content;
    }
}


// Get free allocation space.
Node* getFreeGap(NodeList *list, unsigned size) {
    // start range
    unsigned start = 0;
    unsigned end = size;

    // Iterate over the list to reduce range for the first free space available
    Node *aux = list->start;
    while (aux) {
        // Reduce the range for the first gap available.
        if (aux->startPosition == start) {
            // Move start.
            start += aux->size;
        } else if (end > aux->startPosition && start < aux->startPosition) {
            // move end.
            end = aux->startPosition;
        }

        // When range cross, reset end.
        if (start >= end) {
            end = size;
            aux = list->start;
        } else {
            aux = aux->next;
        }
    }

    // Save free gap
    Node *gap = malloc(sizeof(Node));
    gap->startPosition = start;
    gap->size = end - start;
    gap->next = NULL;
    gap->metadata = NULL;

    return gap;
}

// Allocate blanks spaces on disk and save the information.
void allocateFile(Storage *storage, NodeList **list, unsigned diskSize, unsigned id, char *name, char *content, unsigned size) {
    // Get actual time
    time_t  t;
    time(&t);

    // Save metadata
    Metadata *metadata = malloc(sizeof(Metadata));
    metadata->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(metadata->name, name);
    metadata->size = size;
    metadata->id = id;
    metadata->creationTime = (int) t;
    metadata->uptateTime = (int) t;

    //Saving real file in disk
    FILE *file;
    //Setting directory of file
    char dir[50] = "Files/";
    strcat(dir, name);

    file = fopen(dir, "w");

    //Writing file
    fprintf(file, "%s", content);
    fclose(file);

    // Save the file in disk
    unsigned remaining = size;
    while (remaining > 0) {
        // Get free gap on disk.
        Node *node = getFreeGap(*list, diskSize);

        // Reduce the node size when file is less than the total free space.
        if (remaining < node->size) {
            node->size = remaining;
        }

        // Save file on disk.
        saveOnDisk(storage, id, node->startPosition, node->size);

        // Add metadata on node.
        node->metadata = metadata;

        // Add node to list.
        *list = nodeListInsertEnd(*list, node);

        // Reduce remaining according to the size that was saved.
        remaining -= node->size;

        // Reduce the storage size
        storage->availableSpace -= node->size;
    }
}

int deallocateFile(Storage *storage, NodeList **list, unsigned id) {
    // Temp node.
    Node *temp = NULL;
    Metadata *tempInfo = NULL;

    // Search for the file.
    Node *aux = (*list)->start;
    Node *prev = NULL;
    while (aux && aux->metadata->id != id) {
        prev = aux;
        aux = aux->next;
    }

    // If node is searched.
    if (aux && aux->metadata->id == id) {

        //Next lines for remove real files from disk works on linux only

        //Removing real file in disk
        FILE *file;
        //Setting directory of file to remove
        char dir[50] = "Files/";
        strcat(dir, aux->metadata->name);

        file = fopen(dir, "r");

        //Removing file
        remove(dir);
        fclose(file);

        // Save temp metadata.
        tempInfo = aux->metadata;

        // Remove all nodes of the file.
        do {
            // save node.
            temp = aux;
            // go to next node.
            aux = aux->next;
            // Increase space on disk.
            storage->availableSpace += temp->size;
            // Remove node from list.
            free(temp);
        } while (aux && aux->metadata->id == id);

        // Remove the metadata.
        free(tempInfo);

        // Re-do the pointers.
        if (prev) {
            prev->next = aux;
            if ( !(*list)->end ) {
                (*list)->end = prev;
            }
        } else {
            (*list)->start = aux;
            if ( !aux ) {
                (*list)->end = NULL;
            }
        }

        return 1;
    }

    return 0;
}

void eraseDisk (Storage *storage, NodeList *nodeList, int size) {

    storage->availableSpace = (unsigned int) size;
    for (unsigned i = 0; i<size; i++) {
        storage->data[i].fileID = 0;
//        storage->data[i].logicalAddress = i;
    }


    Node *aux = nodeList->start;
    Node *aux2;
    while (aux) {
        aux2 = aux;
        aux = aux->next;
        if (aux && aux2->metadata->id != aux->metadata->id) {
            free(aux2->metadata);
        } else if (!aux) {
            free(aux2->metadata);
        }
        free(aux2);
    }
    system("rm Files/*");
    system("rm save/*");

    nodeList->start = NULL;
    nodeList->end = NULL;

    printHeader("Disk erased successfully");
}