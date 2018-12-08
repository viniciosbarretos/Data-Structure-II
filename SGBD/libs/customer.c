#include "customer.h"
#include <math.h>

double hashFunction(unsigned accountNumber, unsigned globalDepth) {
    int x = pow(2,globalDepth);
    return (accountNumber % x);
}

void newBucket() {

}

customer newCostumer() {

    customer *c = (customer*) malloc(sizeof(customer));
    printf("\nAcount Number:");
    scanf("%d ", &c->accountNumber);
    printf("\nName:");
    scanf("%s ", c->name);
    printf("\nType(F/J):");
    scanf("%s ", c->customerType);
    printf("\nOverbalance:");
    scanf("%d", &c->overbalance);

    return c;
}

void registerCustomer() {
    customer c = newCostumer();


}

void removeCustomer() {

}

void searchCustomer() {

}
