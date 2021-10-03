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
    int size = lseek(inputFD, 0, SEEK_END);
    char c[TAILLE];
    int i = 0;
    int cpt = 0;
    int nbTaille = size/TAILLE;
    int infTaille = size%TAILLE;
    while(i < size && cpt<numLines && nbTaille>0) {
      lseek(inputFD, -TAILLE, SEEK_CUR);
      read(inputFD, c, sizeof(c));
      int j= sizeof(c);
      while(j >= 0 && cpt<numLines) {
        j--;
        //write(1, &c[j], sizeof(char));
        if(c[j]=='\n') cpt++;
      }
      i+=sizeof(c)-j;
      nbTaille--;
    }
    if(i < size && cpt<numLines && infTaille>0){
        lseek(inputFD, -infTaille, SEEK_CUR);
        char c3[infTaille];
        read(inputFD, c3, sizeof(c3));
        int j= sizeof(c3);
        while(j >= 0 && cpt<numLines) {
          j--;
          //write(1, &c[j], sizeof(char));
          if(c3[j]=='\n') cpt++;
        }
        i+=sizeof(c3)-j;
    }


    //ecriture
    i--;
    //printf("i = %d",i);
    lseek(inputFD, -i, SEEK_END);
    char c2[i];
    read(inputFD,c2,sizeof(c2));
    write(outputFD,c2,sizeof(c2));
    close(inputFD);
    return 0;

}

/*
int main(int argc, char *argv[])
{
    verifier(argc == 4, "il faut 3 paramètres.");

    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    int out = open(argv[2],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, "IDX");

    int pos = atoi(argv[3]);

    return tailRegularFile(in, out, pos);  
 }*/

int main(int argc, char *argv[])
{
    struct stat stat;
    fstat(0, &stat);

    if (!(S_IFREG & stat.st_mode))
    	exit(1);
    return tailRegularFile(0, 1, 10);  
 }