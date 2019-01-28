#include <stdio.h>
#include "student.h"
#include "utils.h"

Student getStudent(int defaultID) {
    // Initialize the costumer.
    Student s;

    s.id = defaultID;

    cleanBuffer();
    // Get costumer information.
    printf("\nName: ");
    scanf("%[^\n]", s.name);
    cleanBuffer();

    printf("\nEmail: ");
    scanf("%[^\n]", s.email);
    cleanBuffer();

    printf("\nAge: ");
    s.age = getIntegerBetween(0, 200);
    cleanBuffer();

    printf("\nType ['a' for active or 'f' for 'finalized']: ");
    s.status = getCharInOptions("af", "Wrong value, try again.\nType ['a' for active or 'f' for finalized]: ");
    cleanBuffer();

    return s;
}