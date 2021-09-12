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
  verifier(argc == 4, "argc");
  int size = atoi(argv[3]);
    FILE* out = fopen(argv[2],"w");
    verifier(out!=NULL,argv[2]);

    FILE* in = fopen(argv[1],"r");
    verifier(in!=NULL,argv[1]);

    int r,w;
    while((r=fread(c,sizeof(char),1,in))!=0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
        w = fwrite(c,sizeof(char),1,out);
        verifier(w==1,"write out");
    }
    verifier(r==0,"read");
    int d = fclose(out);
    verifier(d!=-1,"close");

 
  return EXIT_SUCCESS;
}
