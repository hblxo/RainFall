#include <stdio.h>
#include <stdlib.h>

void run()
{
    fwrite("Good... Wait what?\n", 1, 13, stdout);
    system("/bin/sh");
}

int main()
{
    char buf[56];

    gets(buf);
    return 0;
}