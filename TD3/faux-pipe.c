#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

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
    int i = 0;
    while(i<argc && argv[i]!="|"){
        i++;
    }
    char *cmd1[i+1];
    char *cmd2[argc-i+1];
    i = 1;
    while(i<argc && argv[i]!="|"){
        cmd1[i-1] = argv[i];
        i++;
    }
    i++;
    int tmp = i;
    while(i<argc){
        cmd2[i-1-tmp] = argv[i];
        i++;
    }
    cmd1[sizeof(cmd1)-2]=">";
    cmd1[sizeof(cmd1)-1]="X";

    cmd2[sizeof(cmd1)-2]="<";
    cmd2[sizeof(cmd1)-1]="X";

    if(fork()==0){//child
        execvp(cmd1[0],cmd1);//ou &argv[1]
        perror("exec");
        exit(1);
    }

    if(fork()==0){//child
        execvp(cmd2[0],cmd2);//ou &argv[1]
        perror("exec2");
        exit(1);
    }

    int status;
    wait(&status);
    printf ("*** code de retour : %d\n", valeurStatus(status));

    int status2;
    wait(&status2);
    printf ("*** code de retour 2 : %d\n", valeurStatus(status2));
    return 0;

}