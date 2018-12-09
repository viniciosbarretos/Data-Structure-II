#include "customer.h"
#include "file.h"
#include <math.h>

customer * newCostumer() {

    customer *c = (customer*) malloc(sizeof(customer));
    printf("\nAcount Number:");
    scanf("%d ", &c->accountNumber);
    printf("\nName:");
    scanf("%s ", c->name);

    //Validating customer type.
    do {
        //clearScreen();
        //P: Person, O: Organization
        printf("\nType('P' or 'O'):");
        scanf("%c ", &c->customerType);

        if(c->customerType != 'P' && c->customerType != 'p' && c->customerType != 'O' && c->customerType != 'o') {
            printf("\nWrong value.");
            getchar();
        }

    } while (c->customerType != 'P' && c->customerType != 'p' && c->customerType != 'O' && c->customerType != 'o');

    printf("\nOverbalance:");
    scanf("%d", &c->overbalance);

    return c;
}

void registerCustomer() {
    customer *c = newCostumer();


}

void removeCustomer() {
    int line;
    removeFileLine(line);
}

void searchCustomer() {

}
