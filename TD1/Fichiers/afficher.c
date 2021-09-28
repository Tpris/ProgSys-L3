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

  int index = open(idx_filename,O_RDONLY);
  verifier(index != -1, argv[1]);

  off_t pos = atoi(argv[2]);
  off_t ligne;

  int e =lseek(index,(pos+1)*sizeof(off_t),SEEK_SET);
  read(index, &ligne, sizeof(ligne)); 
  if(pos>0) lseek(in, ligne+1, SEEK_SET); 

  char c[1]; 
  int r;
  while((r=read(in,c,1))>0 && *c!='\n' ){
    putchar(*c);
  }
  
  verifier(r!=-1,"read");
  int cl = close(in);
  verifier(cl!=-1,"close2");

  return EXIT_SUCCESS;
}
