#include <stdint.h>
#include <time.h>
#include <stdlib.h>

void shuffle_ports(uint16_t *array, uint16_t n)
{
    srand(time(NULL));

    for (uint16_t i = n - 1; i > 0; i--) {
        uint16_t j = rand() % (i + 1);

        uint16_t temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
