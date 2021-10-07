#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

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


void verifTime(void (*f)(void), int timeout){
    if(!timeout){
        time_t * t1;
        time(t1);
        f();
        time_t * t2;
        time(t2);
        if(difftime(t1,t2)>timeout) return 124;
    } else {
        f();
    }
}

void sequentiel(int nbTests, char **tests){
    for(int i = 0; i<nbTests; i++){
        pid_t p;
        if((p=fork())==0){
            execlp(tests[i], tests[i],NULL);
            perror(tests[i]);
            exit(1);
        }
    }
}

void paralelle(int nbTests, char **tests){
    
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