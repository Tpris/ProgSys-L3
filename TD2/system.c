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

int System(char* commande){
    // pid_t pid = fork ();
    // if (pid) { // father
    //     int status;
    //     wait (&status);
    //     printf ("retour enfant : %d\n", WEXITSTATUS (status));
    //     return WEXITSTATUS (status);
    // } else {//child
    //     execl("/bin/sh","sh","-c",commande,NULL);
    //     perror("exec");
    //     exit(1);
    // }

    // Correction
    pid_t pid = fork();
    verifier(pid!=-1,"PB fork");

    if(pid==0){
        execl("/bin/sh","sh","-c",commande,NULL);
        perror("exec");
        exit(1);
    }
    waitpid(pid,NULL,0);
    return 0;
}

int main(int argc, char **argv)
{
    System("echo Bonjour");
    System("echo Au revoir");
    //return System(argv[1]);
    return 0;
}
