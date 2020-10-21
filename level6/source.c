#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
    return;
}

void m(void)
{
    puts("Nope");
    return;
}

void main(int ac, char **av)
{
    char *str;
    void (*p)(void) = malloc(4);

    str = malloc(64);
    p = malloc(4);
    p = m;
    strcpy(str, av[1]);
    p();
    return;
}
