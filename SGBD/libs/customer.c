#include "customer.h"
#include "file.h"
//#include "hashing.h"
#include <math.h>

Customer * newCostumer() {

    Customer *c = (Customer*) malloc(sizeof(Customer));
    printf("\nAcount Number:");
    scanf("%d ", &c->id);
    printf("\nName:");
    scanf("%s ", c->name);

    //Validating customer type.
    do {
        //clearScreen();
        //P: Person, O: Organization
        printf("\nType('P' or 'O'):");
        scanf("%c ", c->type);

        if(*(c->type) != 'P' && *(c->type) != 'p' && *(c->type) != 'O' && *(c->type) != 'o') {
            printf("\nWrong value.");
            getchar();
        }

    } while (*(c->type) != 'P' && *(c->type) != 'p' && *(c->type) != 'O' && *(c->type) != 'o');

    printf("\nOverbalance:");
    scanf("%f", &c->overbalance);

    return c;
}

void removeCustomer(int id) {

    int cId = 0;
    printf ("\nType the Client Account Number");
    scanf ("%d", &cId);

//    int hash = calcHash(id, dir->globalDepth);
//    int pos = searchInBucket(dir->key[hash], cId);
//    int line = dir->key[hash]->items[pos].line;
//
//    removeFromDir(dir, id);
//    removeFileLine(line);
}

void searchCustomer(int id) {

}
