/* DO NOT MODIFY THIS FILE */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include "cmdpipe.h"

int main() {

  // test "r"
  //pid_t pr;
  FILE * fr = popen("echo hello", "rfyf");
  if(!fr) { fprintf(stderr,"cmdopen() error!\n"); exit(EXIT_FAILURE); }
  char c;
  while(fread(&c, 1, 1, fr) > 0)
    fwrite(&c, 1, 1, stdout);
  pclose(fr);

  // test "w"
  //pid_t pw;
  FILE * fw = popen("cat", "w");
  if(!fw) { fprintf(stderr,"cmdopen() error!\n"); exit(EXIT_FAILURE); }
  fwrite("hello\n", sizeof(char), 7, fw);
  pclose(fw);

  return EXIT_SUCCESS;
}
