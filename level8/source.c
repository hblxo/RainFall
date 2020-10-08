#include <stdio.h>
#include <string.h>

char *auth = NULL;
char *service = NULL;

int main()
{
    char buf[128];

    while (1)
    {
        printf("%p, %p \n", auth, service);
        if (fgets(buf, 128, stdin) == 0)
            break;
        if (strncmp(buf, "auth ", 5) == 0)
        {
            auth = malloc(4);
            *auth = '\0';
            if (strlen(buf + 5) <= 30)
            {
                strcpy(auth, buf + 5);
            }
        }
        if (strncmp(buf, "reset", 5) == 0)
        {
            free(auth);
        }
        if (strncmp(buf, "service", 7) == 0)
        {
            service = strdup(buf + 7);
        }
        if (strncmp(buf, "login", 5) == 0)
        {
            if (auth[32] == '\0')
            {
                system("/bin/sh");
            }
            else
            {
                fwrite("Password:\n", 1, 10, stdout);
            }
        }
    }
    return (0);
}
