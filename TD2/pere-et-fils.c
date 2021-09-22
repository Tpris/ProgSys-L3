#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

void verifier(int cond, char *s)
{
    if (!cond)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    pid_t pid = fork();
    if (pid)
    { // father
        pprintf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
        wait(0);
    }
    else
    { // Child
        pprintf("je m'appelle %d et je suis le père de %d\n", getpid(), getppid());
    }
/*
    //Fils zombie
    pid_t pid = fork();
    if (!pid)
    { // child
        pprintf("je m'appelle %d et je suis le père de %d\n", getpid(), getppid());
        wait(0);
    }
    else
    { // father
        pprintf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
    }


    //Orphenlin
    pid_t pid = fork();
    if (pid)
    { // father
        pprintf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
    }
    else
    { // Child
        pprintf("je m'appelle %d et je suis le père de %d\n", getpid(), getppid());
    }
*/
    return 0;
}