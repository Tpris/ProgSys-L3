#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void verifier(int cond, char *s)
{
    if (!cond)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}


enum { R, W };



int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    
    return WEXITSTATUS (s);
}

int main(int argc, char **argv)
{
  int tube[2];
  pipe (tube);

  pid_t p1,p2;
  if ((p1=fork ()) == 0) {
    close (tube[0]);
    dup2 (tube[1], 1); close (tube[1]);
    execlp(argv[1],argv[1],NULL);
    perror("exec");
    exit(1);
  } 
  if((p2=fork())==0) { 
    close (tube[1]);
    dup2 (tube[0], 0); close (tube[0]);
    execvp(argv[2],argv+2);
    perror("exec2");
    exit(1);
  }
  close(tube[0]);
  close(tube[1]);
  int status, status2;

  waitpid(p1,&status,0); 
  waitpid(p2,&status2,0);

  int s1 = valeurStatus(status);
  if(s1!=0) return s1;

  return valeurStatus(status2);

}

/**
 * Possible d'inverser code de pere et fils contrairement au faux pipe.
 * 
 * 1.4) tous les close importants
 * 
 * run
 * |
 * pipe--------------
 * |                  |
 * |                  fork
 * |                  dup2
 * fork---            close
 * .      |           close
 * .      dup2        exec
 * .      close
 * .      close
 * .      exec
 * close
 * close
 * wait
 * wait
 * 
 * 
 **/