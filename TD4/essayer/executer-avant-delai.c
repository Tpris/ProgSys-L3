#define _GNU_SOURCE
#include <unistd.h>

#include <sys/wait.h>
#include <stdio.h>

#include "essayer.h"

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    
    return WEXITSTATUS (s);
}

int executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde)
{
  pid_t p;
  if((p=fork())==0){
    alarm(delai_en_seconde);
    essayer(fun,parametre,SIGALRM);
  }
  
  int status;
  waitpid(p,&status,0);

  //parametre = valeurStatus(status);
  printf("rep = %d\n",valeurStatus(status));

  return 0;  
}
