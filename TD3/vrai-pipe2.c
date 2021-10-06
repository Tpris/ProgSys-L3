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

  //Question 1.2
  // for(int i = 1;;i++){
  //   printf("%d\n",i);
  //   write(tube[1],&i,1);
  // }

  //Question 1.3 : return 141 = 128+13 : signal 13 = SIGPIPE
  close(tube[0]);
  char c = 'e';
  write(tube[1],&c,1);
  printf("%s\n",c);

  return 0;

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