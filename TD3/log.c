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
    int out = open(argv[1], O_WRONLY || O_TRUNC || O_CREAT, 0640);

    int tube[2];
    pipe (tube);

    int sortie = dup(1);


    // manip fichier 
    if(fork()==0){
      close (tube[0]);
      dup2 (tube[1], STDOUT_FILENO); close (tube[1]);
        execvp(argv[2],argv+2);
        perror("exec");
        exit(1);
    }

     if (fork() == 0)
     {
 
       close(tube[1]); /* close write side */
 
       /* read some data and print the result on screen */
       while (read(tube[0], out, 1) != 0)
         printf("%s", out);
 
       close(tube[0]); /* close the pipe */
     }

    // wait(0);
    // close (tube[1]);
    // //dup2 (tube[R], STDIN_FILENO); close (tube[R]);
    // write(sortie,tube,sizeof(tube));
    // //printf("%s",tube[0]);

    return 0;
    

}