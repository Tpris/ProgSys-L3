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

int valeurStatus(int s){
    if(WIFSIGNALED(s)) return WTERMSIG(s)+128;
    return WEXITSTATUS (s);
}

int main(int argc, char **argv)
{
    printf("*** execution\n");
    
    if(fork()==0){//child
        execvp(argv[1],argv+1);//ou &argv[1]
        perror("exec");
        exit(1);
    }

    int status;
    wait(&status);
    printf ("*** code de retour : %d\n", valeurStatus(status));
    return 0;

}
