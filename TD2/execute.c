#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h> 

void verifier(int cond, char *s)
{
    if (!cond)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char **argv)
{
    //verifier(argc==1,"Entrez une commande");
    char *argum[argc];
    for(int i = 1; i<argc; i++){
        argum[i-1] = argv[i];
        printf("tab %d: %s",i,argv[i]);
    }
    argum[argc-1] = NULL;

    pid_t pid = fork ();
    if (pid) { // father
        printf("*** execution\n");
        int status;
        wait (&status);
        printf ("retour enfant : %d\n", WEXITSTATUS (status));
    } else {//child
        execvp(argum[0],argum);
        perror("exec");
        return 0;
    }
    return 0;
}
