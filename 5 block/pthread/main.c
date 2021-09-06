/*4. Warcraft. Заданное количество юнитов добывают золото равными порциями из одной шахты, 
задерживаясь в пути на случайное время, до ее истощения. 
Работа каждого юнита реализуется в потоке.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_THREADS 10

typedef struct 
{
    int totalGold;
    int portionGold;
    int workTime;
} MINE;

MINE mine = {1000, 1000 / (NUM_OF_THREADS * 10), 2};
pthread_mutex_t mutex;

void *minus(void *args)
{
    int loc_id = *(int *)args;
    while (1)
    {
        int random = rand() % 1; 
        sleep(mine.workTime + random);
        
        pthread_mutex_lock(&mutex);
        if(mine.totalGold == 0)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        mine.totalGold = mine.totalGold - mine.portionGold;
        printf("mineGold ID = %d GOLD = %d\n", loc_id, mine.totalGold);
        
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}


int main()
{
    pthread_t threads[NUM_OF_THREADS];
    size_t i;
    int id[NUM_OF_THREADS] = {0};
    
    printf("MINEGOLD = %d\n", mine.totalGold);

    //Инициализация мьютекса
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        id[i] = i;
        pthread_create(&threads[i], NULL, minus, &id[i]);
    }

    for (i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    //Уничтожение мьютекса
    pthread_mutex_destroy(&mutex);

    printf("ENDMINEGOLD = %d\n", mine.totalGold);
    return 0;
}