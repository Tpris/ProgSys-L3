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
    verifier(nbFils > 0 && nbFils < 10, argv[1]);

    for(int i = 0; i<nbFils;i++){
        if(fork()==0){
            printf("Je suis le fils %d\n",i);
            exit(0);
        }
    }
    //exit(0);
    return 1;
}