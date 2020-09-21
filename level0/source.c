
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include <unistd.h>

int main(int argc, char **argv)
{
    char *sh;
    uid_t uid;
    gid_t gid;
    char *arg[2];

    if (atoi(argv[1]) == 423)
    {
        sh = strdup("/bin/sh");
        uid = geteuid();
        gid = getegid();

        setresuid(uid, uid, uid);
        setresgid(gid, gid, gid);
        arg[0] = "sh";
        arg[1] = NULL;
        execv(sh, arg);
    }
    else
    {
        fwrite("No !\n", 1, 5, stderr);
    }
    return (0);
}