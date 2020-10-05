#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void p(char *format)
{
    printf(format);
    return;
}

void n(void)
{
    char *s;

    int _m;

    fgets(&s, 512, stdin);
    p((char *)&s);
    if (_m == 0x1025544) // 16930116
    {
        system("/bin/cat /home/user/level5/.pass");
    }
    return;
}

void main(void)
{
    n();
    return;
}
