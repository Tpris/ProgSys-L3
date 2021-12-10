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

sigset_t vide;
pid_t pid;

void my_sig_handler (int sig)
{
  static int nb[32];
  pprintf ("%d[%d]\n",sig,++nb[sig]);
  kill(pid,SIGUSR1);
}

void my_sig_handler_USR (int sig)
{
}

int emetteur(int pere, int argc, char * argv[]) {
  int k = atoi(argv[1]);

  struct sigaction sa;
  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler_USR;
  sigaction (SIGUSR1, &sa, NULL);

  for(int i = 0 ; i < k ; i++) {
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
      sigsuspend(&vide);
  }}

  kill(pere,9);
  return 0;
}


int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());
 
  struct sigaction sa;

  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler;

  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    if(sig!=0 && sig != 2 && sig != 9 && sig != 19 && sig != 17){
      int err = sigaction (sig, &sa, NULL);
      if(err==-1){
        printf("%d;%s\n",sig,strerror(errno));
      }
    }
  }

  sigset_t m;
  sigfillset(&m);
  sigprocmask(SIG_UNBLOCK, &m, NULL);

    
  while(1) 
    pause();
  
  return 0;
}


int main(int argc, char *argv[]){
  sigset_t m;
  sigfillset(&m);
  sigprocmask(SIG_BLOCK,&m,&vide);
  pid = fork();  
  if (pid == 0)
    emetteur(getppid(),argc,argv);
  else
    recepteur(pid);  
}

/**
 * main:
 * On crée un sigset
 * on copie les masks dans le sigset 
 * On les block et on save l'ancienne config
 * 
 * handler :
 * compte et affiche le signal puis envoie le signal SIGUSR1 à l'emmetteur
 * 
 * Recepteur :
 * on applique le handler aux signaux puis on déblock les masques, pas avant sinon ca peut tout faire planter en recevant un signal
 * 
 * Emetteur :
 * On applique un handler vide à SIGUSR1 
 * Puis on envoie les signaux et on attend une rep (usr1)
 * 
 * Schéma :
 * 
 *                   emet    recept
 *   envoie un signal | \     | handler
 *       sigsuspend : |   \   | deblock
 * attend de recevoir |     \ |
 *          un signal |      \| compte signal
 *     pour continuer |      /| envoie SIGUSR1
 *                    |    /  |
 *                    |  /    |
 *     recois SIGUSR1 |/      |
 *           continue | \     |
 *                    |   \   |
 *                    |     \ |
 *                    |      \|
 *                    |      /|
 *                    |    /  |
 *                    |  /    |
 *                    |/      |
 *                
 **/
