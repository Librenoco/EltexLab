// Программа для реализации одной стороны FIFO. Эта сторона сначала пишет, затем читает
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()

{

    int fd;

    // Путь к файлу FIFO

    char *myfifo = "myfifo";

    // Создание именованного файла (FIFO)

    // mkfifo (<путь>, <разрешение>)

    mkfifo(myfifo, 0666);

    char arr1[80], arr2[80];

    while (1)

    {

        // Открыть FIFO только для записи

        fd = open(myfifo, O_WRONLY);

        // Получаем входные данные от пользователя.

        // 80 - максимальная длина

        fgets(arr2, 80, stdin);

        // Записываем ввод arr2ing в FIFO

        // и закрываем

        write(fd, arr2, strlen(arr2) + 1);

        close(fd);

        // Открыть FIFO только для чтения

        fd = open(myfifo, O_RDONLY);

        // Чтение из FIFO

        read(fd, arr1, sizeof(arr1));

        // Распечатать прочитанное сообщение

        printf("User2: %s\n", arr1);

        close(fd);
    }

    return 0;
}