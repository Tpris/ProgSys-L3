
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>

typedef void (*func_t)(void);

jmp_buf buf;

void my_sig_handler(){
    siglongjmp(buf,1);
}

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;

    return WEXITSTATUS (s);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
    struct sigaction sa;
    struct sigaction old;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction(sig,&sa,&old);

    // pid_t pid;
    // if((pid=fork())==0){

        // if(sigsetjmp(buf,1)==0){
        //     f(p);
        //     exit(0);
        // }else
        //     exit(EXIT_FAILURE);

        

        if(sigsetjmp(buf,1)==0){
            f(p);
            sigaction(sig,&old,NULL);
            //exit(0);
            return 0;
        }
        sigaction(sig,&old,NULL);
        //exit(1);
        return 1;

    // }
    // int status;
    // waitpid(pid,&status,0);
    // printf("status : %d\n",valeurStatus(status));
    // return valeurStatus(status);
}
