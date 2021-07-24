/*
4. Найти в строке последовательность одинаковых символов максимальной длины и переписать в выходную строку в виде n1,n2c – начало и 
длина фрагмента и символ, например abcddddddddddddedfg -> 3,12d. Из исходной строки фрагмент удалить. Повторять этот процесс. 
Пока в строке есть последовательности, в конце переписать остаток в выходную строку.
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

#define SIZE 255

void sequenceCharMax(char* , int*, int*, char*);
void deleteSubstring(char*, int*, int*, char*);

int main()
{
    char text[SIZE];
    int start = 0;
    int size = 2;
    char symbol = '\0';
   
    printf("Input string: ");
    scanf("%s", text);
    
    while (size > 1)
    {
        sequenceCharMax(text, &start, &size, &symbol);
        if (size > 1) 
        {
            printf("\n");
            printf("%d , %d%c", start, size, symbol);
            deleteSubstring(text, &start, &size, &symbol);
            printf("\nOutput string: %s\n", text);
        }
    }

    return 0;
}

void sequenceCharMax(char* text, int* startbk, int* sizebk, char* symbolbk)
{
    int startI = 0;
    int endI = 0;
    int position = 0;
    int size = 1;
    char symbol = text[0];

    int sizeMax = 1;
    int startIMax = 0;
    int endIMax = 0;
    char symbolMax = '\0';
    
    for (int i = 0; i < strlen(text) - 1; i++)
    {
        symbol = text[i];
        position = i;
        startI = i;
        while (text[i] == text[i + 1])
            i++;
        endI = i;
        size = endI - startI + 1;

        if (size > sizeMax)
        {
            sizeMax = size;
            startIMax = startI;
            endIMax = endI;
            symbolMax = symbol;
        }
    }
    *startbk = startIMax;
    *sizebk = sizeMax;
    *symbolbk = symbolMax;
}

void deleteSubstring(char* text, int* startDel, int* sizeDel, char* symbolDel)
{
    int sizeArray = strlen(text);
    for (int i = 0; i < (strlen(text) - *startDel - *sizeDel); i++)
    {
        text[*startDel + i] = text[*startDel + *sizeDel + i];
    }
    text[sizeArray - *sizeDel] = '\0';
}