#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void verifier(int i, char *s)
{
  if (!i) {
    perror (s);
    exit (EXIT_FAILURE);
  }
}

int main()
{
    int m = open("file.txt", O_WRONLY | O_TRUNC | O_CREAT, 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(m != -1, "redirection erreur");
    int tmp = dup(1);
    dup2(m, 1);
    int d = close(m); //obligatoire
    verifier(d != -1, "close");

    printf("hello ");
    fflush(stdout);
    write(1, "world", 5);

    dup2(tmp,1);
    close(tmp);//obligatoire
    return 1;
}