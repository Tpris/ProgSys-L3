#define _GNU_SOURCE
#include <unistd.h>

#include <sys/wait.h>
#include <stdio.h>

#include "essayer.h"

struct tmp { 
  void (*fun)(void *); 
  void *parametre; 
  int delai_en_seconde;};



// void executer_avant_dela(void *parametre)
// {
//   struct tmp *x = (struct tmp *) parametre;
//   alarm(x->delai_en_seconde);
//   x->fun(x->parametre);
//   alarm(0);
  
// }

// int executer_avant_delai(void (*fun)(void *), void *parametre, int delai_en_seconde){
//   struct tmp x= {fun,parametre,delai_en_seconde};
//   essayer(executer_avant_dela,&x,SIGALRM);
// }

int executer_avant_delai(void (*fun)(void *), void *parametre, int delai_en_seconde){
  alarm(delai_en_seconde);
  int r = essayer(fun,parametre,SIGALRM);
  //alarm(0);
  return r;
}

// int executer_avant_delai(void (*fun)(void *), void *parametre, int delai_en_seconde){
//   fun(parametre);
//   return 0;
// }