
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

int essayer(void  (*f)(void*), void *p, int sig)
{
    struct sigaction sa;
    struct sigaction old;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction(sig,&sa,&old);

    pid_t pid;
    if((pid=fork())==0){

        // if(sigsetjmp(buf,1)==0){
        //     f(p);
        // }else
        //     exit(-1);

        // exit(0);

        if(sigsetjmp(buf,1)==0){
            f(p);
            sigaction(sig,&old,NULL);
            return 0;
        }
        sigaction(sig,&old,NULL);
        return -1;

    }
    int status;
    waitpid(pid,&status,0);
    return status;
}
