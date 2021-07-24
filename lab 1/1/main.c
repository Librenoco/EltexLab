#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>

#define SIZE 255
#define NULLASCII 48

void numberFinder();
int convertNumberToAscii();
void replaceSabString(int , int , int, char* );

int main()
{ 
    char text[SIZE];
    printf("InputString: "); 
    
    scanf("%s", text);

    numberFinder(text);
    printf("OutputString: %s\n", text);
    return 0;
}

void numberFinder(char* line)
{
    char number[SIZE] = {0};
    int i = 0 , j = 0;
    int iNumber = 0 , startI = 0 , endI=0;
    int numberSystem = 0;
    char numberChar ;
    while (line[i] != '\0') {
        if ((line[i] >= '0') && (line[i] <= '9')) {
            startI = i;
            numberSystem = line[i] - NULLASCII;
            while ((line[i] >= '0') && (line[i] <= '9')) {
                number[j] = line[i];
                
                if (numberSystem <= line[i])
                    numberSystem = line[i] - NULLASCII;
                    
                i++;
                j++;
            }
            endI = i;
            iNumber = atoi(number);
            numberSystem += 1;
            numberChar = convertNumberToAski(iNumber, numberSystem);
            replaceSabString(startI, endI, numberChar, line);
            j = 0;
        }
        i++;
    }
}

int convertNumberToAscii(int number, int numberSystem)
{
    int num = number;
    int result = 0, i = 0;
    while (num > 0)
    {
        result += (num % 10) * (int)pow(numberSystem, i);
        i++;
        num /= 10;
    }
    return result;
}

void replaceSabString(int start, int end, int numberChar, char* line)
{
    for (; start < end; start++)
        line[start] = numberChar;
}