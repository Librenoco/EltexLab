#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 6

int* sabArray(int, int, int*);
int** sequenceIncreasingNumbers(int*, int*);
void printCMD(int**,int);
void cleaner(int**, int);

void printCMD(int** sequenceNumber, int lines)
{
    printf("\n");
    for (int i = 0; i < lines; i++)
    {
        printf("%d: (%d) ", i, sequenceNumber[i][0]);
            for (int j = 1; j <= sequenceNumber[i][0]; j++)
                printf("%d ", sequenceNumber[i][j]);
        printf("\n");
    }
}

void cleaner(int** sequenceNumber, int lines)
{
    for (int i = 0; i < lines; i++)
        free(sequenceNumber[i]);
    free(sequenceNumber);
}

int** sequenceIncreasingNumbers(int* number, int* lines)
{
    int** sequenceNumber = NULL;
    int* outNumber = (int*)malloc(sizeof(int));
    int sequence = 0;
    int size = 0;
    int startI = 0;
    int endI = 0;

    outNumber[0] = 0;
  
    for (int i = 0; i < SIZE; i++)
    {
        if (number[i] < number[i + 1])
        {
            startI = i;
            while (number[i] < number[i + 1])
                i++;
            endI = i;
            size++;

            sequenceNumber = (int**)realloc(sequenceNumber, sizeof(int*) * size);
            sequenceNumber[size - 1] = sabArray(startI, endI, number);
        }else {
            outNumber[0]++;
            outNumber = realloc(outNumber, sizeof(int) * (outNumber[0] + 1));
            outNumber[outNumber[0]] = number[i];
        }
    }
  
    size++;
    sequenceNumber = (int**)realloc(sequenceNumber, sizeof(int*) * size);
    sequenceNumber[size - 1] = outNumber;
    
    *lines = size;

    return sequenceNumber;
}

int* sabArray(int startI, int endI, int* number)
{
    int* sequenceNumber = (int*)malloc(sizeof(int) * (endI - startI + 2));
    sequenceNumber[0] = endI - startI + 1;
    for (int i = 1; i < (endI - startI + 2); i++)
        sequenceNumber[i] = number[startI + i - 1];
    return sequenceNumber;
}

int main()
{
    setlocale(LC_ALL, "ru");
    
    int** sequenceNumber = NULL;
    int lines;

    int number[SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        printf("\n%d: ", i);
        scanf("%d", &number[i]);
    }
  
    sequenceNumber = sequenceIncreasingNumbers(number, &lines);
    
    printCMD(sequenceNumber, lines);
    cleaner(sequenceNumber, lines);
    
    return 0;
}
