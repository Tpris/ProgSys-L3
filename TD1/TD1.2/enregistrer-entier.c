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
    verifier(argc == 4, "argc");
    int out = open(argv[1],O_WRONLY |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    verifier(out != -1, argv[1]);

    off_t pos = atoi(argv[2]); 
    verifier(pos != -1, argv[2]);

    off_t nb = atoi(argv[3]); //Ecrit en binaire
    verifier(nb != -1, argv[3]);

    int n = lseek (out, pos*sizeof(pos), SEEK_SET); // pos * sizeof .. pour ne pas écraser autres nb
    verifier(n != -1, "lseek");

    int w = write(out,&nb, sizeof(nb));
    verifier(w != 1, "write out");

    int d = close(out);
    verifier(d != -1, "close");

    return EXIT_SUCCESS;
}

/**
 * 0000000 000a 0000 0000 0000                    
 * 0000008
 * 
 * premiere colonne pour l'adresse/la ligne
 * 
 **/