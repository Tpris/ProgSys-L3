#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>


int main()
{
    printf("hello ");
    fflush(stdout);
    write(1,"world", 5);
    return 1;
}