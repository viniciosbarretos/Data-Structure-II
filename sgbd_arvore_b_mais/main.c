#include <stdio.h>
#include <stdlib.h>
#include "libs/render.h"
#include "libs/bplustree.h"
#include "libs/student.h"
#include "libs/file.h"
/*
void addStudent(node *root, int defaultId) {

    printHeader("Add a student");
    Student student = getStudent();

    // Get the costumer infos.

    // Insert costumer in dir.
    insertOnDir(dir, id, costumer);

    // Show message
    printHeader("File added!");
}

void deleteCustomer(Dir *dir) {
    int id;
    Item item;

    printHeader("Remove a costumer");

    // Get the costumer id.
    printf ("\nType the Client Account Number: ");
    scanf ("%d", &id);
    cleanBuffer();

    // Search for the item.
    item = searchFromDir(dir, id);

    // Remove or show error.
    if (item.id != -1) {
        removeFromDir(dir, id);
        printHeader("Costumer removed");
    } else {
        printHeader("Costumer not found");
    }
}

void searchCustomer(Dir *dir) {
    int id;
    Item item;
    Customer customer;

    printHeader("Search a costumer");

    // Get the costumer id.
    printf ("\nType the Client Account Number: ");
    scanf ("%d", &id);
    cleanBuffer();

    // Search for the item.
    item = searchFromDir(dir, id);

    // Remove or show error.
    if (item.id != -1) {
        customer = readCustomer(item.line);
        printCostumer(customer);
    } else {
        printHeader("Costumer not found");
    }
}

// Menu options
void printOptions() {
    clearScreen();
    printf("\n[1] - Register Customer\n");
    printf("[2] - Remove Customer\n");
    printf("[3] - Search Customer by Acc number\n");
    printf("[4] - Show Hash Table\n");
    printf("[0] - End Simulation\n");

    printf("\nEnter with your option: ");
}
*/

void readOrDefaultInt(const char *message, int defaultValue, int *result) {
    char buffer[20];

    printf("%s (%d):", message, defaultValue);
    scanf("%s", buffer);
}

void printMenu() {
    printf("\n");
    printHeader("MENU");

    printf("\n\nChoose an option entering the corresponding number:\n\n");
    printf("(1) Insert student record.\n");
    printf("(2) Delete student record.\n");
    printf("(3) Show student list.\n");
    printf("(4) resume.\n");
    printf("(0) EXIT.\n");

    printf("Option:");
}

int main() {
    int result;
    int opt;
    int input_key = 0;
    int key = 0;
    int line = -1;

//    readOrDefault("%d", &result, 15);

    Node * root = NULL;

    //Student s = {1, "tahio", "email", 19, 'a'};

//    for (int i = 0; i < 15; i++) {
//        root = insert(root, i, s);
//    }

    do {
        printMenu();
        (scanf("%d", &opt) != 0);
        //clear screen
        switch (opt) {
            case 1:
                // Get and save the new student.
                line = saveStudent(getStudent(key++));

                // Save the student id on index tree.
                root = insert(root, key, line);

                // Print the tree just for testing.
                print_tree(root);
                break;
            case 2:
                printf("Enter the key corresponding to the student who will be removed");
                scanf("%d", &input_key);
                root = delete(root, input_key);
                print_tree(root);
                break;
            case 3:
                //show student list
                print_leaves(root);
                break;
            case 4:
                //show total pages of the tree and total of KB that is stored
                //printf("\nNumber of pages:%d\n\n", countPages(Node * root));
                break;
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


//    printStudentRow(3826, "Thiago Leal Pozati", "teste@unesp.br", 19, 1);

    return 0;
}

/*
// MAIN
int main(int argc, char ** argv) {

    char * input_file;
    FILE * fp;
    node * root;
    int input_key, input_key_2;
    char instruction;

    root = NULL;
    verbose_output = false;

    if (argc > 1) {
        order = atoi(argv[1]);
        if (order < MIN_ORDER || order > MAX_ORDER) {
            fprintf(stderr, "Invalid order: %d .\n\n", order);
            usage_3();
            exit(EXIT_FAILURE);
        }
    }

    if (argc < 3) {
        license_notice();
        usage_1();
        usage_2();
    }

    if (argc > 2) {
        input_file = argv[2];
        fp = fopen(input_file, "r");
        if (fp == NULL) {
            perror("Failure to open input file.");
            exit(EXIT_FAILURE);
        }
        while (!feof(fp)) {
            fscanf(fp, "%d\n", &input_key);
            root = insert(root, input_key, input_key);
        }
        fclose(fp);
        print_tree(root);
        return EXIT_SUCCESS;
    }

    printf("> ");
    char buffer[BUFFER_SIZE];
    int count = 0;
    bool line_consumed = false;
    while (scanf("%c", &instruction) != EOF) {
        line_consumed = false;
        switch (instruction) {
            case 'd':
                scanf("%d", &input_key);
                root = delete(root, input_key);
                print_tree(root);
                break;
            case 'i':
                fgets(buffer, BUFFER_SIZE, stdin);
                line_consumed = true;
                count = sscanf(buffer, "%d %d", &input_key, &input_key_2);
                if (count == 1)
                    input_key_2 = input_key;
                root = insert(root, input_key, input_key_2);
                print_tree(root);
                break;
            case 'f':
            case 'p':
                scanf("%d", &input_key);
                find_and_print(root, input_key, instruction == 'p');
                break;
            case 'r':
                scanf("%d %d", &input_key, &input_key_2);
                if (input_key > input_key_2) {
                    int tmp = input_key_2;
                    input_key_2 = input_key;
                    input_key = tmp;
                }
                find_and_print_range(root, input_key, input_key_2, instruction == 'p');
                break;
            case 'l':
                print_leaves(root);
                break;
            case 'q':
                while (getchar() != (int)'\n');
                return EXIT_SUCCESS;
                break;
            case 't':
                print_tree(root);
                break;
            case 'v':
                verbose_output = !verbose_output;
                break;
            case 'x':
                if (root)
                    root = destroy_tree(root);
                print_tree(root);
                break;
            default:
                usage_2();
                break;
        }
        if (!line_consumed)
            while (getchar() != (int)'\n');
        printf("> ");
    }
    printf("\n");

    return EXIT_SUCCESS;
}
*/