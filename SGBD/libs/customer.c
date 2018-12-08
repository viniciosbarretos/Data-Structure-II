#include "customer.h"
#include <math.h>

double hashFunction(unsigned accountNumber, unsigned globalDepth) {
    int x = pow(2,globalDepth);
    return (accountNumber % x);
}

void newBucket() {

}

void registerCustomer() {

}

void removeCustomer() {

}

void searchCustomer() {

}
