/* DO NOT MODIFY THIS FILE */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#include "cmdpipe.h"

int main() {

  // test "r"
  pid_t pr;
  FILE * fr = cmdopen("echo hello1", "r", &pr);
  if(!fr) { fprintf(stderr,"cmdopen() error!\n"); exit(EXIT_FAILURE); }
  char c;
  while(fread(&c, 1, 1, fr) > 0)
    fwrite(&c, 1, 1, stdout);
  cmdclose(fr, pr);

  // test "w"
  pid_t pw;
  FILE * fw = cmdopen("cat", "w", &pw);
  if(!fw) { fprintf(stderr,"cmdopen() error!\n"); exit(EXIT_FAILURE); }
  fwrite("hello2\n", sizeof(char), 7, fw);
  cmdclose(fw, pw);

  return EXIT_SUCCESS;
}
