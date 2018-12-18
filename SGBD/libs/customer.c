#include "customer.h"
#include <stdio.h>
#include "file.h"
#include "utils.h"

Customer getCostumer() {
    // Initialize the costumer.
    Customer c;

    // Get costumer information.
    printf("\nName:");
    scanf("%s ", c.name);

    printf("Type ['p' or 'o']:");
    c.type = getCharInOptions("op", "Wrong value.");

    printf("\nOverbalance:");
    scanf("%lf", &c.overbalance);

    return c;
}