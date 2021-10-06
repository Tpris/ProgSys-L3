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

int valeurStatus(int s){
    if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    return WEXITSTATUS (s);
}

int tube[2];

enum { R, W };

void child (char **cmd2)
{
  close (tube[W]);

  dup2 (tube[R], STDIN_FILENO); close (tube[R]);
    execvp(cmd2[0],cmd2);
  perror("exec");
    exit(1);
}

void father (char *cmd1)
{

  close (tube[R]);

  dup2 (tube[W], STDOUT_FILENO); close (tube[W]);
  execlp(cmd1,cmd1,NULL);
  perror("exec");
    exit(1);

}

int main(int argc, char **argv)
{
  pipe (tube);

  if (fork () == 0) { // father
    father (argv[1]);
  } else { //child
    child (argv+2);
  }

}