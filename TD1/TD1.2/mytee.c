#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void verifier(int cond,char*s){
    if(!cond){perror(s);
    exit(EXIT_FAILURE);}}

char c[1];

int main(int argc, char **argv){

    verifier(argc == 2, "argc");
    int out = open(argv[1],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, argv[1]);

    int r,w;
    while((r=read(0,c,1))!=0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
        w = write(1,c,1);
        verifier(w==1,"write 1");
        w = write(out,c,1);
        verifier(w==1,"write out");
    }
    verifier(r==0,"read");
    int d = close(out);
    verifier(d!=-1,"close");


    return 0;
}