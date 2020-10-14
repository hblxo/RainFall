#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int _language = 0;

int greetuser(char *str)
{
    char s1[72]; //[ebp-0x48]

    if (_language == 1)
    {
        strncpy(s1, "Hyvää päivää ", 13); //18 ?
    }
    else if (_language == 2)
    {
        strncpy(s1, "Goedemiddag! ", 13);
    }
    else if (_language == 0)
    {
        strncpy(s1, "Hello ", 6);
    }
    strcat(s1, str);
    puts(s1);
    return 0;
}

int main(int ac, char **av)
{
    int ret;
    char *lang;
    char buf[72];
    char arg[80]; //[esp+0x50]

    if (ac == 3)
    {
        memset(buf, 0, 19);
        strncpy(buf, av[1], 40);
        strncpy(buf + 40, av[2], 32);
        lang = getenv("LANG");
        if (*lang)
        {
            if (!memcmp(lang, "fi", 2)) //fi
                _language = 1;
            else if (!memcmp(lang, "nl", 2))
                _language = 2;
        }
        strncpy(arg, buf, 18);
        ret = greetuser(arg);
    }
    else
    {
        ret = 1;
    }
    return ret;
}
