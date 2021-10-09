// $ ./launch <mode> <timeout> <test1> <test2> [...]

/* a very very simple test framework */

#define _GNU_SOURCE
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define EXIT_TIMEOUT 124
#define EXIT_INVALID 127
#define MAXSTR 255

void print_status(int rank, char* cmd, int wstatus) {
  static char strstatus[MAXSTR];
  if (WIFEXITED(wstatus)) {
    int status = WEXITSTATUS(wstatus);
    if (status == EXIT_SUCCESS)
      snprintf(strstatus, MAXSTR, "SUCCESS (exit %d)", status);
    else if (status == EXIT_TIMEOUT)
      snprintf(strstatus, MAXSTR, "TIMEOUT");
    else if (status == EXIT_INVALID)
      snprintf(strstatus, MAXSTR, "INVALID");
    else
      snprintf(strstatus, MAXSTR, "FAILURE (exit %d)", status);
  } else if (WIFSIGNALED(wstatus)) {
    int sig = WTERMSIG(wstatus);
    snprintf(strstatus, MAXSTR, "KILLED (signal %d)", sig);
  } else
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

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    
    return WEXITSTATUS (s);
}


// void verifTime(void (*f)(void), int timeout){
//     if(!timeout){
//         time_t * t1;
//         time(t1);
//         f();
//         time_t * t2;
//         time(t2);
//         if(difftime(t1,t2)>timeout) return 124;
//     } else {
//         f();
//     }
// }

void paralelle(int nbTests, char **tests){
    for(int i = 0; i<nbTests; i++){
        pid_t p;
        if((p=fork())==0){
            execlp(tests[i], tests[i],NULL);
            perror(tests[i]);
            exit(1);
        }
    }
}

void sequentiel(int nbTests, char **tests){
    if(nbTests>0){
        pid_t p;
        if((p=fork())==0){
            sequentiel(nbTests-1,tests+1);
            exit(0);
        }
        int status;
        waitpid(p,&status,0); 
        execlp(tests[0],tests[0],NULL);
        perror(tests[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char **argv)
{
    verifier(argc >= 3,"arguments manquants");
    int mode = argv[1];
    verifier(mode=="P" || mode=='S', "Entrez 'P' ou 'S' pour le mode");
    int timeout = atoi(argv[2]);

    if(mode == "P"){
        verifTime();
    }
    else if (mode=="S"){

    }

}