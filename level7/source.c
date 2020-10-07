#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char c[80];

int main(int ac, char **av)
{
    char *str1;
    char *str2;
    char *str3;
    char *str4;
    FILE *fp;

    str1 = (int *)malloc(8);
    *str1 = 1;
    str2 = malloc(8);
    str3 = (int *)malloc(8);
    *str3 = 2;
    str4 = malloc(8);
    strcpy(str3[1], av[1]);
    strcpy(str4[1], av[2]);
    fp = fopen("/home/user/level8/.pass", 0x80486e9);
    fgets(c, 0x44, fp);
    puts("~~");
    return 0;
}

void m(void)
{
    time_t t;

    t = time(0);
    printf("%s - %d\n", c, t);
    return;
}
