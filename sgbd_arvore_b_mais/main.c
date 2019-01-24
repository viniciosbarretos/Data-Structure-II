#include <stdio.h>
#include <stdlib.h>
#include "libs/render.h"

int main() {
    printf("Hello world\n");

    printRecordRow(3826, "Thiago Leal Pozati", "teste@unesp.br", 19, 1);

    return 0;
}



// MAIN
/*
int main(int argc, char ** argv) {

    char * input_file;
    FILE * fp;
//    node * root;
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