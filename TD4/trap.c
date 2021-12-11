#include <signal.h>
#include <stdio.h>
#include <setjmp.h>

volatile char *a=NULL;
volatile char b='x';
jmp_buf buf;

void traitant(int s)
{
  printf("signal %d\n", s);
  a = &b;
  longjmp(buf,1);
}

int main()
{
  struct sigaction s;
  char x;

  s.sa_handler = traitant;
  sigemptyset(&s.sa_mask);
  s.sa_flags=0;
  sigaction(SIGSEGV,&s,NULL);

  setjmp(buf);
  
  x = *a;

  printf("fin %c\n",x);
  return 0;
}
