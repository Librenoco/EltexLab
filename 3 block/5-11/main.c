/* Программа, осуществляющая двунаправленную связь через два pipe между процессом-родителем(отправляет строку, получает и выводит количество символов а в строке) 
и процессом-ребенком (получает строку, считает и возвращает количество букв а в строке)  */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_string();

int main()
{
    int fd[2], sf[2], result;
    char* inputString;
    int sizeString = 0;
    char* resstring;

    pipe(fd);
    pipe(sf);

    result = fork();

    if (result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (result > 0)
    {
        printf("\nInput string: ");
        inputString = get_string();
 
        int len = strlen(inputString);
        write(sf[1], &len, sizeof(int));
        write(sf[1], inputString, strlen(inputString));

        int countA  = 0;
        read(fd[0], &countA, sizeof(int));

        printf("The number of letters a in a line: %d\nParent exit\n", countA);
    }
    else
    {
        read(sf[0], &sizeString, sizeof(int));
        resstring = (char *)malloc(sizeof(char) * (sizeString + 1));
        resstring[sizeString] = '\0';
        read(sf[0], resstring, sizeString);
        
        int countA = 0;
            for (int i = 0; i < sizeString; i++)
                if (resstring[i] == 'a')
                countA += 1;

        write(fd[1], &countA, sizeof(int));
        printf("Child exit\n");
    }

    return 0;
}

char *get_string()
{
    int len = 0;
    int capacity = 1;
    char *s = (char *)malloc(sizeof(char));

    char c = getchar();

    while (c != '\n')
    {
        s[(len)++] = c;

        if (len >= capacity)
        {
            capacity *= 2;
            s = (char *)realloc(s, capacity * sizeof(char));
        }

        c = getchar();
    }

    s[len] = '\0';

    return s;
}