#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int cpt = 0;
void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

void my_sig_handler (int sig)
{
  pprintf ("ctrl-c\n");
  cpt++;
}

void new_handler(int sig){
    exit(2);
}

int main(int argc, char *argv[])
{
    
    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction (SIGINT, &sa, NULL);
    pprintf ("Main engages in infinite loop\n");
    while (1){
        if(cpt>=1){
            sa.sa_handler = new_handler;
            sigaction (SIGINT, &sa, NULL);
        }
    }
    
    return 0;

}