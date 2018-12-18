#include "customer.h"
#include <stdio.h>
#include "file.h"
#include "utils.h"

Customer getCostumer() {
    // Initialize the costumer.
    Customer c;

    // Get costumer information.
    printf("\nName: ");
    scanf("%[^\n]", &c.name);
    cleanBuffer();

    printf("\nType ['p' or 'o']: ");
    c.type = getCharInOptions("op", "Wrong value, try again.\nType ['p' or 'o']: ");

    printf("\nOverbalance:");
    scanf("%lf", &c.overbalance);

    return c;
}