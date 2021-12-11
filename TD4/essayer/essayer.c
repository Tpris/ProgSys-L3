
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

void my_sig_handler(int s){
    siglongjmp(buf,s);
}

int valeurStatus(int s){
  if(WIFSIGNALED(s)) return WTERMSIG(s)+128;

    return WEXITSTATUS (s);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
    struct sigaction sa;
    struct sigaction old;
    jmp_buf oldjmp;
    *oldjmp = *buf;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction(sig,&sa,&old);

    int s;
    if((s=sigsetjmp(buf,1))==0){
        f(p);
    }
    if(s!=sig){
        *buf = *oldjmp;
        //sigaction(sig,&old,NULL);
        sigaction(s,&old,NULL);
        raise(s);
        return 0;
    }
    return 1;
}
