#include <stdio.h>
#include "student.h"
#include "utils.h"

Student getStudent(int defaultID) {
    // Initialize the costumer.
    Student s;

    s.id = defaultID;

    // Get costumer information.
    printf("Name: ");
    scanf("%[^\n]", s.name);
    cleanBuffer();

    printf("Email: ");
    scanf("%[^\n]", s.email);
    cleanBuffer();

    printf("Age: ");
    s.age = getIntegerBetween(0, 200);
    cleanBuffer();

    printf("Type ['a' for active or 'f' for 'finalized']: ");
    s.status = getCharInOptions("af", "Wrong value, try again.\nType ['a' for active or 'f' for finalized]: ");
    cleanBuffer();

    return s;
}