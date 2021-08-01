//Программа для реализации одной стороны FIFO. Эта сторона сначала читает, затем читает
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()

{

    int fd1;

    // Путь к файлу FIFO

    char *myfifo = "myfifo";

    // Создание именованного файла (FIFO)

    // mkfifo (<путь>, <разрешение>)

    mkfifo(myfifo, 0666);

    char str1[80], str2[80];

    while (1)

    {

        // Сначала открываем только для чтения и читаем

        fd1 = open(myfifo, O_RDONLY);

        read(fd1, str1, 80);

        // Распечатать прочитанную строку и закрыть

        printf("User1: %s\n", str1);

        close(fd1);

        // Теперь открываем в режиме записи и пишем

        // строка взята у пользователя.

        fd1 = open(myfifo, O_WRONLY);

        fgets(str2, 80, stdin);

        write(fd1, str2, strlen(str2) + 1);

        close(fd1);
    }

    return 0;
}