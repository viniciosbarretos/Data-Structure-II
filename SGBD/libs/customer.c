#include "customer.h"
#include "file.h"
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
        scanf("%c ", c->customerType);

        if(*(c->customerType) != 'P' && *(c->customerType) != 'p' && *(c->customerType) != 'O' && *(c->customerType) != 'o') {
            printf("\nWrong value.");
            getchar();
        }

    } while (*(c->customerType) != 'P' && *(c->customerType) != 'p' && *(c->customerType) != 'O' && *(c->customerType) != 'o');

    printf("\nOverbalance:");
    scanf("%f", &c->overbalance);

    return c;
}

void registerCustomer() {
    Customer *c = newCostumer();


}

void removeCustomer() {
    int line;
    removeFileLine(line);
}

void searchCustomer() {

}
