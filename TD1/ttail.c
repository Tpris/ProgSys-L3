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
    struct stat buf;
    fstat(inputFD, &buf);
    int size = buf.st_size;
    int end = lseek(inputFD, -1, SEEK_END);
    verifier(size==1+end,"lenght file");
    
    off_t i = 0;
    int cpt = 0;

    //Ne compte pas le retour à la ligne de la derniere ligne s'il y en a un 
    char n;
    read(inputFD,&n,1);
    if(n=='\n') cpt--;

    int nbTaille = size/TAILLE;
    int tt = nbTaille;
    int infTaille = size%TAILLE;
    char c[4096];
    int r,w;
    verifier(nbTaille*TAILLE+infTaille==size,"error taille");
    //Lecture par pas de 4096 octets
    while(i < size && cpt<numLines && nbTaille>0) {
      lseek(inputFD, -(i+TAILLE), SEEK_END);
      r = read(inputFD, c, sizeof(c));
      //printf("%s",c);
      verifier(r==TAILLE,"read");
      int j= sizeof(c);
      while(j > 0 && cpt<numLines) {
        j--;
        if(c[j]=='\n') cpt++; //printf("while %c",c[j]);}
      }
      i+=sizeof(c)-j;
      int tmp = sizeof(c)-j;
      printf("j = %d\n",j);
      printf("tmp = %d\n",tmp);
      printf("i = %ld\n",i);
      nbTaille--;
      printf("test\n");
    }
    
    //infTaille = 2853;
    printf("i = %ld, size = %d, cpt = %d, infTaille = %d\n",i,size,cpt,infTaille);

    //Lecture de moins de 4096 octets
    if(i < size && cpt<numLines && infTaille>0){
        lseek(inputFD, -(infTaille+i), SEEK_END);
        char c3[infTaille];
        r = read(inputFD, c3, sizeof(c3));
        verifier(r==infTaille,"read");
        int j= sizeof(c3);
        while(j >= 0 && cpt<numLines) {
          j--;
          if(c3[j]=='\n') {cpt++; printf("toto %c",c3[j]);}
          //printf("testj = %d\n",j);
        }
        i+=infTaille-j;
        printf("test2\n\n");
    }

    //Ecriture
    i--;
    printf("i = %ld\n",i);
    lseek(inputFD, -i, SEEK_END);
    char c2[i];
    r = read(inputFD,c2,sizeof(c2));
    verifier(r==sizeof(c2),"read");
    w = write(outputFD,c2,sizeof(c2));
    verifier(w==sizeof(c2),"write");
    close(inputFD);
    close(outputFD);
    return 0;
}


/* int main(int argc, char *argv[])
{
    verifier(argc == 4, "il faut 3 paramètres.");

    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    int out = open(argv[2],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, "IDX");

    int pos = atoi(argv[3]);

    return tailRegularFile(in, out, pos);  
 } */

 int main(int argc, char *argv[])
{
    struct stat stat;
    fstat(0, &stat);

    if (!(S_IFREG & stat.st_mode))
    	exit(1);
    return tailRegularFile(0, 1, 10);  
 } 