#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void v(void)
{
    char *format;
    int m;

    fgets(&format, 0x200, 0); //0x200 == 512
    printf(&format);
    if (m == 0x40) //0x40 == '@'
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
    return;
}

void main(void)
{
    v();
    return;
}
