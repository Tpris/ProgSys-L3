#include <errno.h>
#include <fcntl.h> 
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TAILLE 4096

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int tailRegularFile(int inputFD, int outputFD, int numLines)
{
    if(inputFD != -1 && outputFD != -1){
        // struct stat buf;
        // fstat(inputFD, &buf);
        // int ls = lseek(inputFD,buf.st_size-numLines,SEEK_SET);
        // if(ls == -1) return 1;
        // char c[numLines];
        // read(inputFD,c,numLines);
        // write(outputFD,c,numLines);
        char c [TAILLE];
        int size = lseek(inputFD, TAILLE*-1, SEEK_END);
        off_t i = 0;
        int cpt= 0;
        int nbTaille = 0;
        while(read(inputFD,c,TAILLE)>0 && cpt < numLines){
          nbTaille++;
          while(cpt < numLines){
              if(c[i]=='\n') cpt++;
              i++;
          }
          lseek(inputFD, TAILLE*-1, SEEK_CUR);
        }
        lseek(inputFD,(nbTaille*TAILLE-i)*-1,SEEK_END);
        printf("test %ld",i*-1);
        int r,w;
        char ch[1];
        while((r=read(inputFD,ch,1))>0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
          w = write(outputFD,ch,1);
          verifier(w==1,"write out");
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    verifier(argc == 4, "il faut 3 paramètres.");

    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    int out = open(argv[2],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, "IDX");

    int pos = atoi(argv[3]);

    return tailRegularFile(in, out, pos);  
 }