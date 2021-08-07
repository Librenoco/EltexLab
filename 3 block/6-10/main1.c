/*Первая программа создаёт сегмент разделяемой памяти и копировать туда свой собственный исходный текст.*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *array; /* Указатель на разделяемую память */
    int shmid; /* IPC дескриптор для области разделяемой памяти */
    int i = 0;
    int flag;
    char pathname[] = "06-1a.c"; /* Имя файла, использующееся для генерации ключа. Файл с таким именем должен существовать в текущей директории */
    long fileSize = 0;
    key_t key; /* IPC ключ */
    FILE *file;
    char fileNamep[] = "main1.c";
    /* Генерируем IPC ключ из имени файла 06-1a.c в текущей директории и номера экземпляра области разделяемой памяти 0 */

    if ((key = ftok(pathname, 0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    file = fopen("main1.c", "rb");
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    printf("%ld\n", fileSize);

    /* Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа, т.е. если для этого ключа она уже существует системный вызов вернет отрицательное значение. Размер памяти определяем как размер массива из 3-х целых переменных, права доступа 0666 - чтение и запись разрешены для всех */
    if ((shmid = shmget(key, fileSize * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {

        /* В случае возникновения ошибки пытаемся определить: возникла ли она из-за того, что сегмент разделяемой памяти уже существует или по другой причине */

        if (errno != EEXIST)
        {

            /* Если по другой причине - прекращаем работу */

            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else
        {

            /* Если из-за того, что разделяемая память уже существует пытаемся получить ее IPC дескриптор и, в случае удачи, сбрасываем флаг необходимости инициализации элементов массива */

            if ((shmid = shmget(key, fileSize * sizeof(char), 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

    /* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. Обратите внимание на то, что для правильного сравнения мы явно преобразовываем значение -1 к указателю на целое.*/

    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    /*Запись файла в разделяемую память*/
    fread(array, sizeof(char), fileSize, file);
    printf("%s\n", array);
    fclose(file);

    if (flag < 0)
    {
        printf("Can not read file\n");
        exit(1);
    }

    if (shmdt(array) < 0)
    {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}