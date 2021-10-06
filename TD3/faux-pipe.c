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
    // int i = 0;
    // while(i<argc && argv[i]!="|"){
    //     i++;
    // }
    // char *cmd1[i+1];
    // char *cmd2[argc-i+1];
    // i = 1;
    // while(i<argc && argv[i]!="|"){
    //     cmd1[i-1] = argv[i];
    //     i++;
    // }
    // i++;
    // int tmp = i;
    // while(i<argc){
    //     cmd2[i-1-tmp] = argv[i];
    //     i++;
    // }
    // cmd1[sizeof(cmd1)-2]=">";
    // cmd1[sizeof(cmd1)-1]="X";

    // cmd2[sizeof(cmd1)-2]="<";
    // cmd2[sizeof(cmd1)-1]="X";

    // if(fork()==0){//child
    //     execvp(cmd1[0],cmd1);
    //     perror("exec");
    //     exit(1);
    // }

    // if(fork()==0){//child
    //     execvp(cmd2[0],cmd2);
    //     perror("exec2");
    //     exit(1);
    // }

    // int status;
    // wait(&status);
    // printf ("*** code de retour : %d\n", valeurStatus(status));

    // int status2;
    // wait(&status2);
    // printf ("*** code de retour 2 : %d\n", valeurStatus(status2));

    
    int out = open("tmp",O_WRONLY | O_TRUNC |O_CREAT , 0600);
    verifier(out != -1,"out");
    if(fork()==0){//child
        
        sleep(1);
        dup2(out,1); close(out);
        execlp(argv[1],argv[1],NULL);
        perror(argv[1]);
        exit(1);
    }
    close(out);
    //wait(0);
    int in = open("tmp",O_RDONLY);
    verifier(in != -1,"in");
    dup2(in,0); close(in);
    execvp(argv[2],argv+2);
    perror(argv[2]);
    exit(1);
    //return 0;

}

/**
 * 
 * 
 * fork
 * |    \
 * wait  open
 * .     dup2
 * .     exec
 * .    /
 * .___/
 * |
 * open
 * dup2
 * exec
 * 
 * 
 * 
 * FILS : ls
 * out --> 3
 * dup2
 * 1--> out
 * close out
 * out -X-> 3
 * 
 * cat cat -n est sensé ecrire ce qu'on tape après la commande en tant réel
 * Ici il n'y a pas de paralellisme. 
 * 
 * 
 * open
 * |
 * fork-------------
 * |                \
 * exec cat -n    sleep1
 * |                .
 * read(0)          .
 * '--> 0           .
 *                  .
 *                exec ls
 * 
 * Lis avant d'avoir écrit => utilisation de tube qui bloque, pas de lecture avant la fin d'ecriture
 * 
 **/