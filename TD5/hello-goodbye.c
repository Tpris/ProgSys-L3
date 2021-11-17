#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <stdint.h>

pthread_barrier_t bar;

void *HelloGoodbye(void *p)
{
  int me = (int)(intptr_t)p;
  printf("%d: bonjour\n", me); 
  pthread_barrier_wait(&bar);
  printf("%d: a bientot\n", me); 

  return NULL;
}

int 
main(int argc, char *argv[])
{

  int NBTHREADS = atoi (argv[1]);

  pthread_t tids[NBTHREADS];
  // int nb[NBTHREADS];

  pthread_barrier_init(&bar, NULL, NBTHREADS); 

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_create (&tids[i], NULL, HelloGoodbye, (void *)(intptr_t)i);
    //CORRECTION DU PROF DE TD
    // nb[i] = i;
    // pthread_create (&tids[i], NULL, Hello, nb+i);
  }

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_join (tids[i], NULL);
  }

  pthread_barrier_destroy(&bar);

  return EXIT_SUCCESS;
}

/**
 * Barriere = point de rendez vous à tous les threads
 * int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned nbThreads); 
 * pthread_barrier_init(&bar, NULL, NBTHREADS); 
 * Limite le coté imprévisible
 **/
