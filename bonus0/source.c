#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void p(char *dest, char *s)
{
    char *ptr;
    char *str;

    puts(s);
    read(0, &str, 4096);
    ptr = strchr(&str, 10);
    *ptr = 0;
    strncpy(dest, &str, 20);
    return;
}

void pp(char *dest)
{
    char c;
    int i;
    char *tmp;
    int j;
    char *s1;
    char *s2;

    j = 0;
    p(s1, " - "); // 0x80486a0 = 0x202d20 -> ' - '
    p(s2, " - "); // 0x80486a0 = 0x202d20 -> ' - '
    strcpy(dest, &s1);
    i = 0xffffffff;
    tmp = dest;
    while (c != '\0')
    {
        if (i == 0)
            break;
        i--;
        c = *tmp;
        tmp = tmp[j * -2 + 1];
    }
    dest[i - 1] = ' '; // 0x80486a4; -> " "
    strcat(dest, &s2);
    return;
}

int main(void)
{
    char buf[54];

    pp(buf);
    puts(buf);
    return 0;
}
