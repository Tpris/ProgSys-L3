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
    char buf[10];
    char dir[100];
    do{
        getcwd(dir, sizeof(dir));
        printf("Priscilla@cmd:%s$ ",dir);
        fflush(stdout);
        read(STDIN_FILENO, buf, 10);
        //fgets(buf,10,stdin);
        int i = 0;
        while(buf[i]!='\0' && i<10){
            if(buf[i]=='\n') buf[i]='\0';
            i++;
        }
        //printf("entrée : %s\n",buf);
        if(strcmp(buf,"\\q")){
            if(fork()==0){
                execlp(buf,buf,NULL);
                perror("exec");
                exit(0);
            }
            else{wait(0);}
        }
    }while(strcmp(buf,"\\q"));
    return 0;
}
