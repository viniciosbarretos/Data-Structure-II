#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "render.h"

void printSequence(const char *str, int times) {
    while ( times > 0 ) {
        printf("%s", str);
        times--;
    }
}

void printDivision(const char *divider, const char *sequence, int size, ...) {
    int i;

    va_list list;
    va_start(list, size);

    for (i = 0; i < size; i ++) {
        printf("%s", divider);
        printSequence(sequence, va_arg(list, int));
    }

    printf("%s\n", divider);
}

void printStudentDivision() {
    printDivision("+", "-", 5, 7, 22, 42, 5, 8);
}

void printStudentRowHeader() {
    printf("| %5s | %20s | %40s | %3s | %6s |\n", "id", "name", "email", "age", "status");
}

// Receive the infos to render a student in a row.
void printStudentRow(int id, const char *name, const char *email, int age, char status) {
    printf("| %5d | %20s | %40s | %3d | %6c |\n", id, name, email, age, status);
}

void printHeader(const char *str) {
    unsigned size = (unsigned) strlen(str);
    printf("\n");
    printSequence("-", size + 8);
    printf("\n-   %s   -\n", str);
    printSequence("-", size + 8);
    printf("\n");
}