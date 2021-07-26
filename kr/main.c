/*
Распределение Диффи - Хелмана
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#pragma warning(disable:4996)

int generator(int);
int powmod(int, int, int );

int main()
{
    int P = 0;
    int r = 0;
    int ma = 0;
    int mb = 0;
    int a = 0;
    int b = 0;
    int ka = 0;
    int kb = 0;

    printf("Enter a large prime number: ");
    scanf("%d", &P);

    r = generator(P);
    
    printf("\nEnter a [1, p-1): ");
    scanf("%d", &a);
    
    ma = powmod(r,a,P);
    printf("ma: %d", ma);
    
    printf("\nEnter b [1, p-1): ");
    scanf("%d", &b);

    mb = powmod(r, b, P);
    printf("mb: %d", mb);
    
    printf("\n-----------------------------");
    
    ka = powmod(mb, a, P);
    printf("\nKa: %d", ka);

    kb = powmod(ma, b, P);
    printf("\nKb: %d\n", kb);

    return 0;
}

int generator(int p) {
    int* fact = (int*)malloc(sizeof(int));
    int size = 1;
    int phi = p - 1;
    int n = phi;

    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) 
        {
            fact = (int*)realloc(fact, sizeof(int) * size);
            fact[size - 1] = i;
            size++;
            while (n % i == 0)
                n /= i;
        }
    if (n > 1) 
    {
        fact = (int*)realloc(fact, sizeof(int) * size);
        fact[size - 1] = n; 
    }

    for (int res = 2; res <= p; ++res) 
    {
        bool ok = true;

        for (size_t i = 1; i < size && ok; ++i)
            ok &= powmod(res, phi / fact[i - 1], p) != 1;
        if (ok)  
            return res;
    }
    
    return -1;
}

int powmod(int a, int b, int p) {
    int res = 1;
    
    for (int i = 0; i < b; i++)
        res = (res * a) % p;
        
    return res;
}
