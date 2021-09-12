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

char c[1];

int 
main(int argc, char **argv)
{
  verifier(argc == 3, "argc");
    int out = open(argv[2],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, argv[1]);

    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    int r,w;
    while((r=read(in,c,1))!=0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
        w = write(out,c,1);
        verifier(w==1,"write out");
    }
    verifier(r==0,"read");
    int d = close(out);
    verifier(d!=-1,"close");

 
  return EXIT_SUCCESS;
}
