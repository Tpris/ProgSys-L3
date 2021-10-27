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

pid_t pid;
sigset_t vide;

void my_sig_handler_USR1 (int sig)
{

}

void my_sig_handler (int sig)
{
  static int nb[32];
  pprintf ("%d[%d]\n",sig,++nb[sig]);
  struct sigaction s;
  s.sa_flags = 0;
  sigemptyset (&s.sa_mask);
  s.sa_handler = my_sig_handler_USR1;
  sigaction(SIGUSR1,&s,NULL);

  kill(pid,SIGUSR1);
}



int emetteur(int pere, int argc, char * argv[]) {

  // sigset_t m;
  
  // sigfillset(&m);
  // sigprocmask(SIG_BLOCK,&m,NULL);
  
  struct sigaction s;
  s.sa_flags = 0;
  sigemptyset (&s.sa_mask);
  s.sa_handler = my_sig_handler_USR1;
  sigaction(SIGUSR1,&s,NULL);

  int k = atoi(argv[1]);

  //sleep(1); 
  // sigset_t new_mask;
  // sigfillset(&new_mask);
  // sigdelset(&new_mask,SIGUSR1);

  for(int i = 0 ; i < k ; i++) 
    for(int j = 2; j < argc; j++){
      kill(pere,atoi(argv[j]));
      //pause();
      sigsuspend(&vide);
  }

  kill(pere,9);
  return 0;
}


int recepteur(int fils) {
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT  
  struct sigaction sa;
  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);
  sa.sa_handler = my_sig_handler;

  //sigaction(SIGINT,&sa,NULL);

  for(int sig = 0 ; sig < NSIGNORT ; sig++) {
    if(sig!=0 && sig != 9 && sig != 19 && sig != 2){ 
      int err = sigaction (sig, &sa, NULL);
      if(err==-1){
        fprintf(stderr,"%d;%s\n",sig,strerror(errno));
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
  sigprocmask(SIG_BLOCK, &m, &vide);

  pid = fork();
  if (pid == 0){
    emetteur(getppid(),argc,argv);
  }else{
    recepteur(pid);  
  }
}

/**
 * Ici le but est de changer le comportement de tous les signaux (de 0 à 32)
 * La modification des signaux 0, 9 et 19 provoquent des erreurs. Ces signaux sont géré directement par
 * le noyau sans passer par le programme. Kill (9) n'envoie pas de signal au processus pour lui dire
 * qu'il va mourir, il le tue directement.
 * Donc dans le for de la fonction reception on met un if pour ne pas changer ces signaux (j'ai aussi
 * mis le 2(SIGINT = ctrl c) pour pouvoir arreter le programme facilement)
 * 
 * Dans le handler on a mis un tableau de compteur pour chaque signal. Il est en static et dans le 
 * print on a fait ++nb[sig] pour que ça ajoute 1 et que ça affiche le résultat contrairement à 
 * nb[sig]++ qui fait l'inverse.
 * 
 * 
 * 
 * 
 * PERE
 * sigpropmask
 * fork()
 * |    \
 * |    sigpropmask
 * |      |
 * |    kill
 * |    /
 * |----
 * sigpropmask
 * 
 * on ut sig prop mask
 * ________
 * |  _    |
 * | |_|   |
 * ----------
 * | |  
 * 
 **/
