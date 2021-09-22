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
  int tmp = dup(1);
  dup2(m, 1);
  int d = close(m); //obligatoire
  verifier(d!=-1,"close");

  f();

  dup2(tmp,1);
  close(tmp);//obligatoire
  /**
   * de base :
   * 1-> term
   * m -> fichier
   * Dup2 :
   * 1-> fichier
   * m plus utilisé -> close
   * f()
   * Dup2:
   * tmp->1
   * tmp plus utile -> close
   * 
   **/
}

int main(int argc, char *argv[])
{
  printf ("*** DEBUT ***\n");

  rediriger_vers (quelques_prints, "sortie.txt");

  printf ("*** FIN ***\n");

  return EXIT_SUCCESS;
}
  
