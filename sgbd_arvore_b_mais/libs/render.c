#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "render.h"

#define stdoutSize = 80;

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

void printStudentBlock(int id, const char *name, const char *email, int age, char status) {

    printDivision("+", "-", 1, 50);
    printf("| id:     %40d |\n", id);
    printf("| Name:   %40s |\n", name);
    printf("| Email:  %40s |\n", email);
    printf("| Age:    %40d |\n", age);
    printf("| Status: %40c |\n", status);
    printDivision("+", "-", 1, 50);
}

// Todo better header.
void printHeader(const char *str) {
    unsigned size = (unsigned) strlen(str);
    printf("\n");
    printSequence("-", size + 8);
    printf("\n-   %s   -\n", str);
    printSequence("-", size + 8);
    printf("\n");
}

void printMenu() {
    printf("\n");
    printHeader("MENU");

    printf("\n\nChoose an option entering the corresponding number:\n\n");
    printf("[1] - Insert student record.\n");
    printf("[2] - Delete student record.\n");
    printf("[3] - Show student list.\n");
    printf("[4] - Resume.\n");
    printf("[5] - Find student by id.\n");
    printf("[0] - Exit.\n\n");

    printf("Option: ");
}