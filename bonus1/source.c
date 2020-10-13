#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
    int ret;
    char buf[40];
    int n;

    n = atoi(av[1]);
    if (n < 10)
    {
        memcpy(buf, av[2], n * sizeof(int));
        if (n == 0x574f4c46) // WOLF
        {
            execl("/bin/sh", "sh", 0);
        }
        ret = 0;
    }
    else
    {
        ret = 1;
    }
    return ret;
}
