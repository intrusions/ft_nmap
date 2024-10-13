#include "inc.h"

void shuffle_ports(u16 *array, u16 n)
{
    srand(time(NULL));

    for (u16 i = n - 1; i > 0; i--) {
        u16 j = rand() % (i + 1);

        u16 temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
