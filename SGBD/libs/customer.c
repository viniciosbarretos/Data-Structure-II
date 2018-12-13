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
        printf("\nType('I' or 'B'):");
        scanf("%c ", &c->customerType);

        if(c->customerType != 'I' && c->customerType != 'i' && c->customerType != 'B' && c->customerType != 'b') {
            printf("\nWrong value.");
            getchar();
        }

    } while (c->customerType != 'I' && c->customerType != 'i' && c->customerType != 'B' && c->customerType != 'B');

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
