#include <stdio.h>
#include <stdlib.h>
#include "libs/render.h"
#include "libs/bplustree.h"
#include "libs/student.h"
#include "libs/file.h"
#include "libs/utils.h"
#include "libs/persist.h"

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

Node* deleteStudent(Node *root) {
    int id;

    printHeader("Remove student");

    // Print the students.
    printf("Actual students: \n");
    print_leaves(root);

    // Get the id of student.
    printf("Enter the id corresponding to the student who will be removed.\nId: ");
    scanf("%d", &id);

    // Delete the student.
    root = delete(root, id);

    waitForChar("\nPress any key to continue...");

    return root;
}


int main() {
    int opt;
    int key = 0;
    Node * root = NULL;

    // Restore the students in file to tree and get the last id used.
    key = hydrateFile(&root) + 1;

    do {
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
                //show student list
                printHeader("Students");
                print_leaves(root);

                waitForChar("\nPress any key to continue...");
                break;
            case 4:
                //show total pages of the tree and total of KB that is stored
                //printf("\nNumber of pages:%d\n\n", countPages(Node * root));
                break;
            case 5:
                //Search for a student by id

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
    print_leaves(root);

    return 0;
}