#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[])
{
    verifier(argc>=3, "Arguments manquant");
    int out = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0640);
    verifier(out != -1, argv[1]);

    int tube[2];
    pipe (tube);

    if(fork()==0){
      close (tube[0]);
      dup2 (tube[1], STDOUT_FILENO); close (tube[1]);
        execvp(argv[2],argv+2);
        perror("exec");
        exit(1);
    }
    close(tube[1]);
    char c;
    while (read(tube[0], &c, 1) != 0){ 
      write(1,&c,1);
      write(out,&c,1);
    }
      
    close(tube[0]); 

    return 0;
    

}