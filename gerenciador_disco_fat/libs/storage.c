#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "storage.h"

/*
 * system.dat
 * ---------------------------------------------------
 * 1;1;1;1;1;1;2;2;2;5;5;4;4;4;4;5;5;5;5;\n // storage
 * 1{metadata}
 * 0{node}
 * 0{node}
 * 1{metadata}
 * 0{node}
 * 1{metadata}
 * 0{node}
 */

/*
 * Dehydrate the storage data.
 * */

//Saving StorageState in a real file storage.txt
void dehydrateStorage(FILE *file, Storage *storage) {
    file = fopen("storage.txt","w");

    fwrite(storage, sizeof(storage),1,file);

//    for(int i = 0; i < 300; i++) {
//        fprintf(file, "%d,%d\n", storage->data[i].logicalAddress, storage->data[i].fileID);
//    }
    fclose(file);
}

void dehydrateNodeList(FILE *file, NodeList *nodeList) {
    file = fopen("node.txt","w");
    Node *aux = nodeList->start;
    while(aux != NULL) {
        fwrite(aux, sizeof(Node),1,file);
        //fprintf(file, "%d, %s, %d, %d, %d, %d\n", aux->metadata->id, aux->metadata->name, aux->metadata->size, aux->metadata->creationTime, aux->startPosition, aux->size);
        aux = aux->next;
    }
    fclose(file);
}

void dehidrate(Storage *storage, NodeList *nodeList) {
    FILE *file1 = NULL, *file2 = NULL;

    dehydrateStorage(file1,storage);
    dehydrateNodeList(file2,nodeList);
}

/*
 * Hydrate the storage data.
 * */

Storage* hydrateStorage(FILE *file) {

}

NodeList hydrateNodeList(FILE *file) {

}

void hidrate(Storage **pStorage, NodeList **pNodeList) {
    *pStorage = hydrateStorage();
    *pNodeList = hydrateNodeList();
}

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

//Node* getFreeGap(NodeList *list, unsigned size) {
//    // start range
//    unsigned start = 0;
//    unsigned end = size;
//
//    // Locate start of the gap.
//    Node *aux = list->start;
//    while (aux) {
//        if (aux->startPosition == start) {
//            // Move start.
//            start += aux->size;
//            aux = list->start;
//        } else {
//            aux = aux->next;
//        }
//    }
//
//    // Locate end of the gap.
//    aux = list->start;
//    while (aux) {
//        if (end > aux->startPosition && start < aux->startPosition) {
//            // move end.
//            end = aux->startPosition;
//        }
//        aux = aux->next;
//    }
//
//    // Save free gap
//    Node *gap = malloc(sizeof(Node));
//    gap->startPosition = start;
//    gap->size = end - start;
//    gap->next = NULL;
//    gap->metadata = NULL;
//
//    return gap;
//}


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

//void stringCopy(char *out, const char *in) {
//    unsigned i = 0;
//    while (in[i] != '\0') {
//        out[i] = in[i];
//        i++;
//    }
//    out[i] = '\0';
//}

// Allocate blanks spaces on disk and save the information.
void allocateFile(Storage *storage, NodeList **list, unsigned diskSize, unsigned id, char *name, char *content, unsigned size) {
    // Get actual time
    time_t  t;
    time(&t);

    // Save metadata
    Metadata *metadata = malloc(sizeof(Metadata));
    metadata->name = (char*) malloc(sizeof(strlen(name) + 1));
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
        }

        return 1;
    }

    return 0;
}


/*
// Create file content and call createData function to insert it into storage
void allocateFile(Storage *disk, FAT *fat, char *name, char *content, unsigned size, unsigned id) {
    // Allocate file node on memory
    File *newFile = malloc( sizeof(File) );

    // Save information on file.
    strcpy(newFile->name, name);
    strcpy(newFile->content, content);
    newFile->id = id;
    newFile->size = size;

    // Allocate file on disk.
    newFile->fatStartPosition = createData(disk, fat, size, newFile->id);
    // Save file pointer on its first entry on fat table.
    fat[newFile->fatStartPosition].fileAddress = newFile;
}
*/


/*
// Initialize the table creating an array of FAT structure.
// Each position of array represents a table row with direct access.
FAT* initializeTable(unsigned storageSize) {
    // Allocate the Fat table on memory.
    FAT *fat = malloc (sizeof(FAT) * storageSize);

    // Clears all FAT positions.
    for (unsigned i=0; i<storageSize; i++) {
        fat[i].block = NULL;
        fat[i].fileAddress = NULL;
        fat[i].nextAddress = 0;
    }

    return fat;
}
*/



/*
// Insert data into storage and reference in table
unsigned createData(Storage *disk, FAT *fat, unsigned size, unsigned id) {
    unsigned blockAdded = 0, i = 0, first=0;
    int prevAddress = - 1;

    // i<storageSize don't is checked because this code
    // will only execute if storage have available space

    // Add blocks for first available position.
    while (blockAdded<size) {
        if (fat[i].block == NULL) {
            // Save information in the disk and in the table.
            disk->data[i].fileID = id;
            fat[i].block = &disk->data[i];
            fat[i].nextAddress = -1;

            if (!blockAdded) {
                first = i;
            } else {
                fat[prevAddress].nextAddress = i;
            }

            // Update flags.
            prevAddress = i;
            blockAdded++;
            disk->availableSpace--;
        }
        i++;
    }

    // Return the position that files start on table
    return first;
}
*/

/*
// Remove file in the storage and table
void deallocateFile(Storage *disk, FAT *fat, int i) {
    int next;

    // Delete file
    free(fat[i].fileAddress);

    // While isn't the last portion of table, clean it.
    while(i != -1) {
        next = fat[i].nextAddress;
        // Remove references from disk.
        fat[i].block->fileID = 0;
        fat[i].block = NULL;

        // Remove references from table.
        fat[i].fileAddress = NULL;
        fat[i].nextAddress = 0;

        // Increase disk space.
        disk->availableSpace++;

        // Go to next portion of file.
        i = next;
    }
}
 */
