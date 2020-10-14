#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
    int ret;
    FILE *file;
    int n;
    char buf[66];
    char str[66];

    memset(buf, 0, 66);
    file = fopen("/home/user/end/.pass", "r"); // 0x80486f0
    if ((file == NULL) || (ac != 2))
        ret = -1;
    else
    {
        fread(buf, 1, 66, file);
        n = atoi(av[1]);
        buf[n] = '\0';
        fread(str, 1, 65, file);
        fclose(file);
        if (!strcmp(buf, av[1]))
            execl("/bin/sh", "sh", 0);
        else
            puts(str);
        ret = 0;
    }
    return ret;
}
