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
    char a[100];
    int size = 0;
    int c = 0;
    int b = 0;

    if ((pfd = pipe(fd)) < 0)
    {
        printf("ошибка");
        exit(1);
    }
    else
    {
        do
        {
            c = write(fd[1], "h", 2);
            b = read(fd[0], a, 1);
            size++;
            printf("%dKb\n", (int)(size / 1024));
        } while (c != b);
    }
    
    return 0;
}