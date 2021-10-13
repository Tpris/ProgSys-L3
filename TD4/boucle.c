#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

struct sigaction old;
void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

void my_sig_handler (int sig)
{
  pprintf ("ctrl-c\n");
  //sigaction (SIGINT, &old, NULL);
  /* //autre solution
  struct sigaction sa;
  sa.handler = SIG_DEFAULT;
  */
}

int main(int argc, char *argv[])
{
    
    struct sigaction sa;
    //sa.sa_flags = 0;
    sa.sa_flags = SA_RESETHAND; // restore signal par défault apres 1er signal
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction (SIGINT, &sa, &old);
    pprintf ("Main engages in infinite loop\n");
    while (1);
    
    return 0;

}