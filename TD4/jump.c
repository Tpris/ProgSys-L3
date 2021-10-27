#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>

#define NSIGNORT 32

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

jmp_buf buf;
int i = 0;

void g(){
    longjmp(buf,1);
}

void traitement(){
    pprintf("%d\n",i);
    i++;
    if(i<10) g();
}

void f(){
    setjmp(buf);
    traitement();
}

int main(int argc, char *argv[]){

    // setjmp(buf);
    // pprintf("%d\n",i);
    // i++;
    // if(i<10) longjmp(buf,1);

    f();

    return 0;
}