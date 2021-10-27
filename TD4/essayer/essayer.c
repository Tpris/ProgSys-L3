
#include "essayer.h"

#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stddef.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef void (*func_t)(void);

jmp_buf buf;

void my_sig_handler(){
    longjmp(buf,1);
}

int essayer(void  (*f)(void*), void *p, int sig)
{
    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset (&sa.sa_mask);
    sa.sa_handler = my_sig_handler;
    sigaction(sig,&sa,NULL);

    if(setjmp(buf)==0){
        // int devNull = open("test",O_WRONLY | O_TRUNC |O_CREAT , 0640);
        // int tmp = dup(1);
        // dup2(devNull, 1);
        // int d = close(devNull); //obligatoire

        f(p);

        // dup2(tmp,1);
        // close(tmp);
    }else
        return -1;
    return 0;
}
