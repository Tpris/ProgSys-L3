#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


void verifier(int i, char *s)
{
  if (!i) {
    perror (s);
    exit (EXIT_FAILURE);
  }
}

void quelques_prints (void)
{
  printf ("Juste");
  printf (" histoire");
  printf (" de tester...\n");
  printf ("...que la redirection");
  printf (" marche !\n");
}

void rediriger_vers (void (*f)(void), char *file)
{
  int m = open(file,O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
  verifier(m != -1, "redirection erreur");

  dup2(m, 1);

  char c[1];
  int r,w;
  while((r=read(f,c,1))!=0){// 0 = lecture clavier, 1 = sortie, 2 = erreur
      w = write(m,c,1);
      verifier(w==1,"write out");
  }
  verifier(r==0,"read");

  int d = close(m);
  verifier(d!=-1,"close");
}

int main(int argc, char *argv[])
{
  printf ("*** DEBUT ***\n");

  rediriger_vers (quelques_prints, "sortie.txt");

  printf ("*** FIN ***\n");

  return EXIT_SUCCESS;
}
  
