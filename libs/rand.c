#include <stdlib.h>

long int random(void);

int getRandom(int min, int max) {
    return min + (int) random() % (max - min);
}
