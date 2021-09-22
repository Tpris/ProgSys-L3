#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void verifier(int cond, char *s)
{
    if (!cond)
    {
        perror(s);
        exit(EXIT_FAILURE);
    }
}

char c[1];

int main(int argc, char **argv)
{
    int err = open("ERREURS-LIRE.log",O_WRONLY |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(err != -1, "redirection erreur");
    dup2(err, STDERR_FILENO);
    int e = close(err);
    verifier(e!=-1,"close2");

    verifier(argc == 3, "argc");
    int in = open(argv[1],O_RDONLY);
    verifier(in != -1, argv[1]);

    off_t pos = atoi(argv[2]);

    int n = lseek (in, pos*sizeof(pos), SEEK_SET);
    verifier(n != -1, "lseek");

    off_t val;
    int r=read(in,&val,sizeof(val));
    verifier(r==sizeof(val),"read");

    printf("nb : %ld\n",val);

    int d = close(in);
    verifier(d!=-1,"close");

    return EXIT_SUCCESS;
}