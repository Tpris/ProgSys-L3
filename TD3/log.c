#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}



int main(int argc, char *argv[])
{
    verifier(argc>=3, "Arguments manquant");
    int out = open(argv[1], O_WRONLY || O_TRUNC || O_CREAT, 0640);

    int tube[2];
    pipe (tube);

    int sortie = dup(stdout);

    dup2(tube[1],1); close(tube[1]);

    // manip fichier 

    execvp(argv[2],argv+2);

}