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
     int out = open(argv[1],O_WRONLY | O_TRUNC |O_CREAT , 0640); // 640 = droit : user 110 grp 100 other 000
    
    verifier(out != -1, argv[1]);

    int pos = atoi(argv[2]);
    verifier(pos != -1, argv[2]);

    u_int32_t nb = atoi(argv[3]);
    verifier(nb != -1, argv[3]);

    int n = lseek (out, pos, SEEK_SET);

    int w = write(out,&nb, sizeof(u_int32_t));
    //verifier(w == sizeof(u_int32_t), "write out");

    int d = close(out);
    verifier(d != -1, "close");

    return EXIT_SUCCESS;
}