#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h> 
#include <dirent.h>
#include <fnmatch.h>

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
    // char *argum[argc];
    // for(int i = 1; i<argc-1; i++){
    //     argum[i-1] = argv[i];
    // }
    // argum[argc-2] = NULL;
    // DIR *dir = opendir(argv[argc-1]);
    // //if(dir!=NULL){
    //     pid_t pid = fork ();
    //     if (pid) { // father
    //         printf("*** execution\n");
    //         int status;
    //         wait (&status);
    //         printf ("retour enfant : %d\n", WEXITSTATUS (status));
    //     } else {//child
    //         execvp(argum[0],argum);
    //         perror("exec");
    //         exit(1);
    //     }
    // //}
    // return 0;

    // Correction
    DIR *dir = opendir(".");
    verifier(dir!=NULL,".");
    struct dirent *r;
    char*motif = argv[argc-1];
    while ((r = readdir(dir)) != NULL){
        if(!fnmatch(motif, r->d_name,0)){
            //printf("- %s\n",r->d_name);
            if(fork() == 0){
                argv[argc-1]= r->d_name;
                execvp(argv[1],argv+1);
                perror("exec");
                exit(1);
            }
            else{
                wait(NULL);
                closedir(dir);
                return 0;
            }
        }
    }
    return 0;
}
