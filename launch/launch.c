// $ ./launch <mode> <timeout> <test1> <test2> [...]

/* a very very simple test framework */

#define _GNU_SOURCE
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <signal.h>

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <sys/types.h>
#include <sys/time.h>

#define EXIT_TIMEOUT 124
#define EXIT_INVALID 127
#define MAXSTR 255

#define TIME_DIFF(t1, t2) \
  ((t2.tv_sec - t1.tv_sec) + ((double)(t2.tv_usec - t1.tv_usec)) / 1000000)


struct timeval fin;

void print_status(int rank, char *cmd, int wstatus)
{
  static char strstatus[MAXSTR];
  if (WIFEXITED(wstatus))
  {
    int status = WEXITSTATUS(wstatus);
    if (status == EXIT_SUCCESS)
      snprintf(strstatus, MAXSTR, "SUCCESS (exit %d)", status);
    else if (status == EXIT_TIMEOUT)
      snprintf(strstatus, MAXSTR, "TIMEOUT");
    else if (status == EXIT_INVALID)
      snprintf(strstatus, MAXSTR, "INVALID");
    else
      snprintf(strstatus, MAXSTR, "FAILURE (exit %d)", status);
  }
  else if (WIFSIGNALED(wstatus))
  {
    int sig = WTERMSIG(wstatus);
    snprintf(strstatus, MAXSTR, "KILLED (signal %d)", sig);
  }
  else
    snprintf(strstatus, MAXSTR, "UNDEFINED");

  printf("Test #%d: %s => %s\n", rank, cmd, strstatus);
}

void verifier(int cond, char *s)
{
  if (!cond)
  {
    perror(s);
    exit(EXIT_FAILURE);
  }
}


void my_sig_handler(int sig){
  gettimeofday(&fin,NULL);
}

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s);
  return WEXITSTATUS (s);
}


int main(int argc, char **argv)
{
  verifier(argc >= 3, "arguments manquants");
  char mode = argv[1][0];
  verifier((mode == 'P' || mode == 'S') && !argv[1][1], "Entrez 'P' ou 'S' pour le mode");
  int timeout = atoi(argv[2]);

  pid_t p[argc - 3];
  int status[argc - 3];
  for (int i = 0; i < argc - 3; i++)
  {
    if ((p[i] = fork()) == 0)
    {
      char name[sizeof(i) + 4];
      sprintf(name, "%d.log", i);
      int sortie = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0640);
      dup2(sortie, 2); 
      dup2(sortie, 1);
      close(sortie);

      struct sigaction time;
      time.sa_handler = my_sig_handler;
      sigemptyset (&time.sa_mask);
      time.sa_flags = SA_RESTART;
      int t = sigaction(SIGCHLD,&time,NULL);

      pid_t p;
      int s;
      struct timeval debut;
      gettimeofday(&debut, NULL);
      if((p=fork())==0){
      execlp(argv[i + 3], argv[i + 3], NULL);
      perror(argv[i + 3]);
      exit(EXIT_INVALID);
      }
      if(timeout){
        sleep(timeout);
        kill(p,9);
      }
      waitpid(p, &s, 0);
      if(timeout && s==9 && TIME_DIFF(debut,fin)>=timeout) exit(EXIT_TIMEOUT);
      if(WIFSIGNALED(s)) raise(WTERMSIG(s));
      exit(valeurStatus(s));

    }
    if (mode == 'S'){
      waitpid(p[i], &status[i], 0);
    }
  }
  if (mode == 'P') {
    for (int i = 0; i < argc - 3; i++)
    {
      waitpid(p[i], &status[i], 0);
    }
  }
  for (int i = 0; i < argc - 3; i++)
  {
    print_status(i, argv[i + 3], status[i]);
  }
  for (int i = 0; i < argc - 3; i++)
  {
    if(valeurStatus(status[i])!=0) return 1;
  }
  return 0;
}