#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

void p(void)
{
    uint32_t addr;
    char *src;

    fflush(stdout);
    gets(src);
    if ((addr & 0xb0000000) == 0xb0000000)
    {
        printf("(%p)\n", addr);
        exit(1);
    }
    puts(src);
    strdup(src);
    return;
}

int main(void)
{
    p();
    return 0;
}
