#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
#include <stdint.h>

void *HelloGoodbye(void *p)
{
  int me = (int)(intptr_t)p;

  printf("%d: bonjour\n", me); 
  sleep(1);
  printf("%d: a bientot\n", me); 

  return NULL;
}

void *Hello(void *p)
{
  int me = (int)(intptr_t)p;

  printf("%d: bonjour\n", me); 

  return NULL;
}

void *Goodbye(void *p)
{
  int me = (int)(intptr_t)p;

  printf("%d: a bientot\n", me); 

  return NULL;
}

int 
main(int argc, char *argv[])
{

  int NBTHREADS = atoi (argv[1]);

  pthread_t pids[NBTHREADS];

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_create (&pids[i], NULL, Hello, (void *)(intptr_t)i);
  }

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_join (pids[i], NULL);
  }

  printf("----------\n");

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_create (&pids[i], NULL, Goodbye, (void *)(intptr_t)i);
  }

  for (int i = 0; i < NBTHREADS; i++) {
    pthread_join (pids[i], NULL);
  }

  return EXIT_SUCCESS;
}
