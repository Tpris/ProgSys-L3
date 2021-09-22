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
    // pid_t pid = fork();
    // if (pid)
    // { // father
    //     wait(0);
    //     printf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
    // }
    // else
    // { // Child
    //     printf("je m'appelle %d et je suis le fils de %d\n", getpid(), getppid());
    // }

    // //Fils zombie
    // pid_t pid = fork();
    // if (pid)
    // { // father
    //     getchar();
    //     printf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
    // }
    // else
    // { // Child
    //     printf("je m'appelle %d et je suis le fils de %d\n", getpid(), getppid());
    // }

    /**
     * run
     * |
     * fork
     * |    \
     * |        \
     * getchar()  printf()
     * |            |
     * |          exit()
     * |            |
     * |          Zombie
     * printf
     * 
     * 
     **/


    //Orphenlin
    pid_t pid = fork();
    if (pid)
    { // father
        printf("je m'appelle %d et je suis le père de %d\n",getpid(), pid);
    }
    else
    { // Child
        getchar();
        printf("je m'appelle %d et je suis le fils de %d\n", getpid(), getppid());
    }
    return 0;

    /**
     * run
     * |
     * fork
     * |    \
     * |        \
     * |          getchar()
     * |          printf()
     * |            |
     * |          exit()
     * |            |
     * |          Zombie
     * printf
     * 
     * 
     * ./a.out
     * A pere de B
     * prompt [appuyer sur entrer] 
     * B fils de X
     * 
     * shell
     * |
     * fork
     * |    \
     * |        \
     * |          pere
     * wait       prompt
     * |            /\
     * |        exit() \
     * |        /       \         
     * printf---        
     * 
     **/
}