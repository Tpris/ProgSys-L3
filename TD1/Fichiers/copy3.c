#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}



int 
main(int argc, char **argv)
{
  verifier(argc == 4, "argc");
    int out = open(argv[2],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, argv[1]);
    int size = atoi(argv[3]);

    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    char c[size];

    int r,w;
    while((r=read(in,c,size))>0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
        w = write(out,c,r);
        verifier(w==r,"write out");
    }
    verifier(r==0,"read");
    int d = close(out);
    verifier(d!=-1,"close");

 
  return EXIT_SUCCESS;
}
