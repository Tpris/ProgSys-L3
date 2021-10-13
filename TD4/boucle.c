#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

/*1*/
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
  /*1*/
  // sigaction (SIGINT, &old, NULL);
  /*2*/
  // struct sigaction sa;
  // sa.sa_handler = SIG_DFL; //signal par default
  // sigaction (SIGINT, &sa, NULL);
 
}

int main(int argc, char *argv[])
{
    
    struct sigaction sa;
    /*1 et 2*/
    // sa.sa_flags = 0;
    /*3*/
    sa.sa_flags = SA_RESETHAND; // restore signal par défault apres 1er signal
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    /*1*/
    // sigaction (SIGINT, &sa, &old);
    /*2 et 3*/
    sigaction (SIGINT, &sa, NULL);
    pprintf ("Main engages in infinite loop\n");
    while (1);
    
    return 0;

}

/**
 * J'ai repris le code catch vu en amphi pour modifier le signal.
 * 
 * On a pas encore vu pourquoi on met :
 * sa.sa_flags = 0;
 * sigemptyset (&sa.sa_mask);
 * 
 * mais ce qui est important pour l'instant c'est le handler. La fonction avec laquelle on l'initialise
 * définira le comportement lors de la récéption du signal.
 * 
 * Pour que le signal reprenne sa fonction par défault au bout de la 2e fois il y a 3 solutions :
 * 
 * 1) On déclare en global une struct sigaction qu'on initialise dans le main en renseignant son adresse
 * dans le 3e parametre de sigaction. Cela permet de sauvegarder l'ancienne configuration du signal.
 * Ensuite dans le handler (my_sig_handler) on peut de nouveau appeler la fonction sigaction qui 
 * modifiera de nouveau le signal. On peut mettre ici en 2e parametre la sauvegarde faite précédemment.
 * 
 * 2) On déclare et initialise dans le handler une struct sigaction. Le handler lors de son 
 * initialisation : SIG_DFL remet la fonction du signal par default.
 * 
 * 3) Dans le main on initialise juste le flag avec SA_RESETHAND ce qui a pour effet de restaurer 
 * automatique le traitement du signal apres la premiere reception un signal.
 * 
 * La meilleure solution est la 3 puis la 1 puis la 2.
 **/