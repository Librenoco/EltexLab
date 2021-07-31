/*
6. Последовательность структурированных переменных типа struct man { char name[20]; int  dd,mm,yy; char* addr; }; 
Последняя компонента представляет собой строку переменной размерности, расположенную непосредственно за структурированной переменной.
Конец последовательности - структурированная переменная с пустой строкой в поле name.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct man
{
    char name[20]; 
    int dd;
    int mm;
    int yy;
    char* addr;
} Man; 

void inputData(Man*, int);
void outputData(Man*, int);
char* get_string();

void main()
{
    int size = 0;
    
    printf("Input count note: ");
    scanf("%d", &size);
    Man *note = (Man*)malloc(sizeof(Man) * size); 
    inputData(note, size);
    outputData(note, size);
    free(note);
}

void inputData(Man* note, int size)
{ 
    for (int i = 0; i < size; i++)
    {
        system("clear");
        
        printf("%d:\n", i + 1);
        
        printf("Name: ");
        scanf("%s", note[i].name);
        
        printf("\ndd,mm,yy: ");
        scanf("%d %d %d", &(note[i].dd), &(note[i].mm), &(note[i].yy));
        
        getchar();
        printf("\naddr: ");
        note[i].addr = get_string();
    }
}

void outputData(Man* note, int size)
{
    system("clear");

    for (int i = 0; i < size; i++)
    {
        printf("%d:\n", i + 1);

        printf("Name: %s", note[i].name);

        printf("\ndd,mm,yy: %d %d %d", note[i].dd, note[i].mm, note[i].yy);

        printf("\naddr: %s", note[i].addr);

        printf("\n");
    }
}

char* get_string() {
    int len = 0; 
    int capacity = 1; 
    char* s = (char*)malloc(sizeof(char)); 

    char c = getchar(); 

    while (c != '\n') {
        s[(len)++] = c; 

        if (len >= capacity) {
            capacity *= 2;
            s = (char*)realloc(s, capacity * sizeof(char));
        }

        c = getchar();       
    }

    s[len] = '\0';

    return s;
}
