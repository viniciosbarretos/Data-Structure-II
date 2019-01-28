#include <stdio.h>
#include <stdlib.h>
#include "libs/render.h"
#include "libs/bplustree.h"
#include "libs/student.h"
#include "libs/file.h"
#include "libs/utils.h"
#include "libs/persist.h"


// Add an student for the db.
Node* addStudent(Node *root, int key) {
    int line;
    Student student;

    printHeader("Add student");

    // Get and save the new student.
    student = getStudent(key);
    line = saveStudent(student);

    // Save the student id on index tree.
    root = insert(root, key, line);

    // Print the student inserted.
    printf("\nStudent inserted successfully\n");
    printStudentBlock(student.id, student.name, student.email, student.age, student.status);

    waitForChar("\nPress any key to continue...");

    return root;
}


// Find and delete an student by his id.
Node* deleteStudent(Node *root) {
    int id;

    printHeader("Remove student");

    // Print the students.
    printf("Actual students: \n");
    print_leaves(root);

    // Get the id of student.
    printf("Enter the id corresponding to the student who will be removed.\nId: ");
    scanf("%d", &id);

    // Search for student.
    Record *record = find(root, id, false, NULL);

    if (record) {
        // Remove user from the file.
        removeStudent(record->line);

        // Delete the student.
        root = delete(root, id);

        printf("\nUser deleted successfully\n");
    } else {
        printf("\nUser not found.\n");
    }

    waitForChar("\nPress any key to continue...");

    return root;
}


// Search for a student by id and print it.
void findStudent(Node *root) {
    int id;
    Student student;

    // Get the id of student.
    printf("Enter the id corresponding to the student who will be removed.\nId: ");
    scanf("%d", &id);

    // Search for student.
    Record *record = find(root, id, false, NULL);

    if (record) {
        // Get the student.
        readStudent(record->line);

        // Print the student.
        printStudentBlock(student.id, student.name, student.email, student.age, student.status);
    } else {
        printf("\nUser not found.");
    }

    waitForChar("\nPress any key to continue...");

}


// Print all students on db.
void showStudentsList(Node *root) {
    //show student list
    printHeader("Students");
    print_leaves(root);

    waitForChar("\nPress any key to continue...");
}


int main() {
    int opt;
    int key = 0;
    Node * root = NULL;

    // Restore the students in file to tree and get the last id used.
    key = hydrateFile(&root) + 1;

    do {
        clearScreen();
        // Show menu.
        printMenu();
        opt = getIntegerBetween(0, 4);
        cleanBuffer();

        clearScreen();
        switch (opt) {
            case 1:
                root = addStudent(root, key++);
                break;
            case 2:
                root = deleteStudent(root);
                break;
            case 3:
                showStudentsList(root);
                break;
            case 4:
                //show total pages of the tree and total of KB that is stored
                //printf("\nNumber of pages:%d\n\n", countPages(Node * root));
                printHeader("RESUME");
                resume(root);
                waitForChar("\nPress any key to continue...");
                break;
            case 5:
                findStudent(root);
            case 0:
                printf("Bye bye :( \n");
                break;
            default:
                printf("Invalid option!!\nTry again!\n");
                break;
        }
    } while (opt != 0);
    printf("\n");

    print_tree(root);

    return 0;
}