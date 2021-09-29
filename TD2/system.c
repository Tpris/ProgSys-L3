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

int systeme(char* commande){
    pid_t pid = fork ();
    if (pid) { // father
        int status;
        wait (&status);
        printf ("retour enfant : %d\n", WEXITSTATUS (status));
    } else {//child
        execlp(commande,commande,NULL);
        perror("exec");
        exit(0);
    }
}

int main(int argc, char **argv)
{
    return systeme(argv[1]);
}
