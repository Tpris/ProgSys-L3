#define XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define NSIGNORT 32

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  sleep(1); 

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
  }

  //kill(pere,9);
  return 0;
}

void my_sig_handler (int sig)
{
  static int nb[32];
  pprintf ("%d[%d]\n",sig,++nb[sig]);
}

int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT  

    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;

    for(int sig = 0 ; sig < NSIGNORT ; sig++) {
      if(sig!=0 && sig != 9 && sig != 19 && sig != 2){
      //sigaction( , , ); 
        int err = sigaction (sig, &sa, NULL);
        if(err==-1){
          fprintf(stderr,"%d;%s\n",sig,strerror(errno));
        }
      }

  }
    
  while(1) 
    pause();
  
  return 0;
}


int main(int argc, char *argv[]){
  pid_t pid = fork();  
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}
