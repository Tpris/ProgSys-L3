#include <fcntl.h> 
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/mman.h>
#include <assert.h>


#define TAILLE 4096

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int tailRegularFile(int inputFD, int outputFD, int numLines)
{

    int len = lseek(inputFD, 0, SEEK_END);
    int i = len-1;
    int cpt = 0;

    char * buffer = mmap(NULL, len,PROT_READ, MAP_SHARED,inputFD,0);
    assert(buffer!=NULL);
    
    // while(i >= 0 && cpt<numLines) {
    //   if(buffer[i]=='\n') cpt++;
    //   i--;
    // }

    // while(i<len-1){
    //   i++;
    //   printf("%c",buffer[i]);
    // }

    //CORRECTION
    
    // int pos = len;
    // for(pos; pos>=1 && numLines>0;pos--){
    //   if(buffer[pos-1]=='\n') numLines--;
    // }
    // pos++;

    int pos = len-1;
    for(pos; pos>=1;pos--){
      if(buffer[pos-1]=='\n') numLines--;
      if(numLines==0) break;
    }
    pos++;
    write(outputFD,buffer+pos, len-pos);

    return 0;
}

int main(int argc, char *argv[])
{
    struct stat stat;
    fstat(0, &stat);

    if (!(S_IFREG & stat.st_mode))
    	exit(1);
    return tailRegularFile(0, 1, 10);  
 }
