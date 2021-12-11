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
volatile int i = 0;

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

    // volatile int i = 0; // avec -O3 tjrs 0 donc on met volatile pour ne pas qu'il y ait d'optimisation dessus
    // setjmp(buf);
    // pprintf("%d\n",i);
    // i++;
    // if(i<10) longjmp(buf,1);

    f();

    return 0;
}



// void f(){
//     longjmp(buf,1);
// }
// void g(){
//     setjmp(buf);
// }
// int main(int argc, char *argv[]){

//     volatile int i = 0; // avec -O3 tjrs 0 donc on met volatile pour ne pas qu'il y ait d'optimisation dessus
//     //g();
//     setjmp(buf);
//     pprintf("%d\n",i);
//     i++;
//     if(i<10) f();

//     return 0;
// }

/**
 * 
 * setjmp = struct machin jmp[1] : permet d'avoir l'adresse et l'allocation en mm temps : sauvegarde dans un tab l'ensemble des registres
 * longjump dépile les fonctions imbriquées
 * le contexte d'execution de setjump doit tjrs etre actif
 **/