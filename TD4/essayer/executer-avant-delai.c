#define _GNU_SOURCE
#include <unistd.h>

#include <sys/wait.h>
#include <stdio.h>

#include "essayer.h"

struct tmp { void (*fun)(void *); void *parametre; int delai_en_seconde;}

int exe(;;;){
  struct tmp x= {f,p,delai}
  essayer(executer_avant_delai,x,SIGALRM);
}

int executer_avant_delai(void *parametre)
{
  struct tmp *x = (struct tmp) p;
  alarm(delai_en_seconde);
  x->fun(x->p);
  alarm(0);
  return r;
  
}
