#include "persist.h"
#include "utils.h"

//Recover the SGBD state by the file.
int hydrateFile(Node **root) {

    // Open the file.
    FILE *file = fopen("SGBD.txt", "r");

    int lineCounter = 0;
    int maxId = -1;

    int aux;
    int id;

    if(file) {
        while(fscanf(file, "%d, %d", &aux, &id) == 2) {
            // Verifies if is an valid data, "1" Copies or "0" Jumps.
            if (aux) {
                // Insert the student on index tree.
                *root = insert(*root, id, lineCounter);
            }

            // Save the max id read.
            maxId = max(maxId, id);

            // Go to the next student.
            fseek(file, 73, SEEK_CUR);

            // Increment line counter.
            lineCounter++;
        }
        fclose(file);
    }
    return maxId;
}