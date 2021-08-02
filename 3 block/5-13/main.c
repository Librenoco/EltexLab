/* Программа определяет размер pipe для операционной системы.*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int pfd = 0;
    int fd[2];
    int size = 0;

    pipe(fd);

    do
    {
        write(fd[1], "h", 1);
        size++;
        printf("%dKb\n", (int)(size / 1024));
    } while (1);

    return 0;
}