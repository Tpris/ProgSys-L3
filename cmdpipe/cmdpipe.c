#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "cmdpipe.h"

FILE * cmdopen(const char *command, const char *type, pid_t * pid)
{
  if(!(type[0]=='w'||type[0]=='r') || type[1]!='\0'){
    perror("type error");
    exit(1);
  }
  int tube[2];
  pipe(tube);
  FILE *f;

  if((*pid=fork())==0){
    if(type[0]=='w'){
      close(tube[1]);
      dup2(tube[0],0);
      close(tube[0]);
    }
    if(type[0]=='r'){
      close(tube[0]);
      dup2(tube[1],1);
      close(tube[1]);
    }
    execl("/bin/sh","sh","-c",command,NULL);
    perror("error exec");
    exit(1);
  }
  
  if(type[0] == 'r'){
    f = fdopen(tube[0], type);
    close(tube[1]);
  }
  if(type[0] == 'w') {
    f = fdopen(tube[1], type);
    close(tube[0]);
  }
	
  return f;
}

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    
    return WEXITSTATUS (s);
}

int cmdclose(FILE * stream, pid_t pid)
{
  fclose(stream);
  int status; 
  waitpid(pid,&status,0);
  return valeurStatus(status);
}
