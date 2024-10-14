#include "inc.h"

void random_usleep()
{
    srand(time(NULL));
    u32 delay = 1000 + rand() % 1000;
    usleep(delay);
}
