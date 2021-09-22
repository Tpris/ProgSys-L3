#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf("[PID %d] " format, getpid(), ##__VA_ARGS__)

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
    verifier(argc == 2, "argc");
    int nbFils = atoi(argv[1]);
    verifier(nbFils > 0, argv[1]);

    for(int i = 0; i<nbFils;i++){
        if(fork()==0){
            printf("Je suis le fils %d\n",i);
            exit(0);
        } 
        //wait(0);//2*
    } 
    //wait(0);//1*
    for(int i = 0; i<nbFils; i++){wait(0);}//3*
    return 0;
}

/**
 * Partage tete de lecture ?
 * retour du fork() dans les registres != selon processus et il est copié dans la mémoire
 * 
 * 1*
 * run
 * |
 * fork
 * |   \
 * |   printf
 * |   exit(0)
 * fork     |
 * |   \    |
 * |   printf
 * |   exit(0)
 * .        |
 * .        |
 * .      /
 * |    /
 * wait(0)
 * 
 * 2*
 * run
 * |
 * fork
 * |     \
 * wait  printf
 * |     exit(0)
 * fork     |
 * |     \  |
 * wait printf
 * |    exit(0)
 * .        |
 * .        |
 * .      /
 * |    /
 * wait(0)
 * 
 * 
 * 3*
 * run
 * |
 * fork
 * |   \
 * |   printf
 * |   exit(0)
 * fork     |
 * |   \    |
 * |   printf
 * |   exit(0)
 * .        |
 * .        |
 * .      /
 * |    /
 * wait(0)
 * wait(0)
 * .
 * .
 * wait(0)
 * 
 **/