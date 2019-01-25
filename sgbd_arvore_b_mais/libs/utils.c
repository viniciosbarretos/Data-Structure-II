#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Clean buffer after a text input
void cleanBuffer() {
    int i;
    while ((i = getchar()) != '\n' && i != EOF);
}

// Copy from input to buffer in a certain range.
void strCopyFragment(char *buffer, const char *input, int start, int size) {
    int i;
    // if copy can be made.
    if ( (int) strlen(input) >= start+size) {
        // Copying all the chars
        for (i=0; i<size; i++) {
            buffer[i] = input[i+start];
        }
        // Add end to buffer.
        buffer[i] = '\0';
    }
}

// Convert a char toLowerCase
char toLower(char c) {
    return tolower(c);
}

// Convert string to lowerCase
void toLowerCase(char *str) {
    int i;
    int m = (int) strlen(str);

    for(i=0; i<m; i++) {
        str[i] = tolower(str[i]);
    }
}

// Get a integer inside a range.
int getIntegerBetween(int min, int max) {
    int n;

    do {
        scanf("%d", &n);
        if (n < min || n > max) {
            printf("Number must be between %d and %d\nTry again: ", min, max);
        }
    } while (n < min || n > max);

    return n;
}

// Get a integer inside a range.
char getCharInOptions(const char *options, const char *errorMessage) {
    char t;
    int i, n, isValid;

    // Get the size of the options.
    n = (int) strlen(options);

    // Set isValid to false.
    isValid = 0;

    do {
        scanf("%c", &t);

        // Iterate over all possibilities.
        for (i = 0; i < n && !isValid; i++) {
            if (t == toLower(options[i])) {
                isValid = 1;
            }
        }

        if (!isValid) {
            printf("%s", errorMessage);
        }

    } while (!isValid);

    // Return the character
    return t;
}

