#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
#define BUF_SIZE 2048


void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]){
  verifier(argc == 2, "il faut un paramètre.");

  // construire le chemin au fichier index
  int l = strlen(argv[1]) ;
  char idx_filename[l + strlen(SUFFIXE) + 1];
  strncpy(idx_filename, argv[1], l);
  strcpy(idx_filename + l, SUFFIXE);

  // ... 
  int in = open(argv[1],O_RDONLY);
  verifier(in != -1, argv[1]);

  int index = open(idx_filename,O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
  verifier(index != -1, "IDX");

  char c;
  int r,w;

  off_t pos = 0;
  write(index, &pos,sizeof(pos));
  write(index, &pos,sizeof(pos));
  for(off_t pos = 0; (r=read(in, &c, 1)) > 0; pos++){
      if(c=='\n'){
        w = write(index, &pos,sizeof(pos));
      }
  }
  verifier(r==0,"read");
  int d = close(index);
  verifier(d!=-1,"close");
  int dd = close(in);
  verifier(dd!=-1,"close2");

  return EXIT_SUCCESS;
}

/**
 * \n = 0a
 * 
 * 
 **/
