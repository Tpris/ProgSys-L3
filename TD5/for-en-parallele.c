#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long volatile k = 0;
const unsigned long MAX = 100 * 1000;

pthread_mutex_t m;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //remplace le init dans main

void *for_en_parallele(void *p)
{
  pthread_mutex_lock(&m);
  for(unsigned long i=0; i < MAX; i++){
    k++;
  }
  pthread_mutex_unlock(&m);
  return NULL;
}

int 
main(int argc, char *argv[])
{

  int n = atoi(argv[1]);
  pthread_t tids[n];

  pthread_mutex_init(&m,NULL);
 
  for(int i = 0; i <n ; i++)
    pthread_create(tids + i, NULL, for_en_parallele, NULL);

  for(int i = 0; i <n ; i++)
    pthread_join(tids[i],NULL);
  
  pthread_mutex_destroy(&m);

  printf("%lu\n",k);

  return EXIT_SUCCESS;
}

/**
 * 
 * for i++ 
 *  | x nbThreads
 *  V
 * ld
 * inc
 * sto
 * ld
 * inc
 * sto
 * ld
 * inc
 * sto
 * 
 * = 6
 * 
 * mauvais mélange de 2 threads:
 * ld
 * ld
 * inc 
 * sto 1
 * inc
 * sto 1
 * 
 * = 1 au lieu de 2
 * 
 * verrou = exclusion mutuelle = sas avec une file d'attente
 * 
 * lock for i++ unlock mieux que lock i++ unlock : réduit le nb de lock et de possibilités de paralelisation
 * 
 **/
