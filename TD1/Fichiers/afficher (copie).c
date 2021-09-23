#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  verifier(argc == 3, "il faut deux paramètres.");

  // construire le chemin au fichier index
  int l = strlen(argv[1]) ;
  char idx_filename[l + strlen(SUFFIXE) + 1];

  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  //...

  int in = open(argv[1],O_RDONLY);
  verifier(in != -1, argv[1]);

  off_t pos = atoi(argv[2]);
  off_t ligne;

  
  read(in, &ligne, sizeof(ligne)); // initialise ligne
  //printf("Ligne : %ld",sizeof(ligne));
  
  // char c[1]; 
  // int r;
  // int cpt = 0;
  // int size = 0;
  // while((r=read(in,c,1))>0 && cpt<pos){
  //   if(*c=='\n') cpt++;
  //   size++;
  // }
  
  //if(pos>1){
  lseek(in,(pos/*-2*/)*sizeof(ligne),SEEK_SET);
  //lseek(in,size,SEEK_SET);
  //}
  //lseek(in, ligne+1, SEEK_SET); //correction avec ligne+1 ???

  char c[1]; 
  int r;
  while((r=read(in,c,1))>0 /* && *c!='\n' */){
    putchar(*c);
  }

  verifier(r!=-1,"read");
  int cl = close(in);
  verifier(cl!=-1,"close2");

  return EXIT_SUCCESS;
}
