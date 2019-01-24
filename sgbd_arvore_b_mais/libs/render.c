#include <stdio.h>
#include <stdarg.h>
#include "render.h"

void printSequence(const char *str, int times) {
    while ( times > 0 ) {
        printf("%s", str);
        times--;
    }
}

void printRecordDivision(const char *divider, const char *sequence, int size, ...) {
    int i;

    va_list list;
    va_start(list, size);

    for (i = 0; i < size; i ++) {
        printf("%s", divider);
        printSequence(sequence, va_arg(list, int));
    }

    printf("%s\n", divider);
}

// Receive the infos to render a racord in a row.
void printRecordRow(int id, const char *name, const char *email, int age, short int status) {
    printRecordDivision("+", "-", 5, 11, 28, 49, 10, 11);
    printf("| id: %5d | name: %20s | email: %40s | age: %3d | status: %1d |\n", id, name, email, age, status);
    printRecordDivision("+", "-", 5, 11, 28, 49, 10, 11);
}