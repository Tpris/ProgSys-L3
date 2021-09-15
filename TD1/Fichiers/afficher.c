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

  int index = open(idx_filename,O_WRONLY |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
  verifier(index != -1, "IDX");

  off_t pos = atoi(argv[2]);
  off_t ligne;

  if(pos>1){
  lseek(index,(pos-2)*sizeof(ligne),SEEK_SET);
  }
  read(index, &ligne, sizeof(ligne));
  lseek(in, ligne+1, SEEK_SET);

  char c; 
  int r,w;
  while((r=read(in,&c,1))>0 && c!='\n'){
    putchar(c);
  }

  verifier(r==0,"read");
  int d = close(index);
  verifier(d!=-1,"close");
  int dd = close(in);
  verifier(dd!=-1,"close2");

  return EXIT_SUCCESS;
}
