/*
Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. В перечень функций входят:
    • ввод записи таблицы с клавиатуры;
    • загрузка и сохранение  таблицы в текстовом файле;
    • просмотр таблицы;
    • сортировка таблицы в порядке возрастания заданного поля;
    • поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
    • удаление записи;
    • изменение (редактирование) записи;
    • вычисление с проверкой и использованием всех записей по заданному условию и формуле (например, общая сумма на всех счетах).

Перечень полей структурированной переменной:
    14. Название кинофильма, сеанс, стоимость билета, количество зрителей.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cinema
{
    char* name;
    int dd;
    int mm;
    int hours;
    int minutes;
    int price;
    int viewers;
} Cinema;

void inputData(Cinema*, int);
void outputData(Cinema*, int);
void editData(Cinema*, int);
int save(const char* filename, Cinema* p, int);
Cinema* load(const char* filename, int*);
char* get_string();
void deleteNote(Cinema*, int, int*);
int findeNote(Cinema*, int);

int main()
{
    const char* filename = "test.dat";
    int choise = 0;
    int size = 0;
    int numberRecord = 0;
    int edit = 0;

    printf("Enter the size of the table: ");
    scanf("%d", &size);

    Cinema* note = (Cinema*)malloc(sizeof(Cinema) * size);
    printf("\n");

    system("clear");

    while (choise != 8)
    {
        system("clear");
        printf("-------------------------------\n");
        printf("1. Insert data into table\n");
        printf("2. Loading the table\n");
        printf("3. Saving the table\n");
        printf("4. Table view\n");
        printf("5. Edit a record in the table\n");
        printf("6. Delete a record in the table\n");
        printf("7. Find\n");
        printf("8. Exit\n");
        printf("-------------------------------\n");
        printf("Choise: ");
        scanf("%d", &choise);

        switch (choise)
        {
        // Первичное заполнение таблицы
        case 1:
            if (edit == 0)
            {
                system("clear");
                inputData(note, size);
                edit = 1;
            }
            else 
            {
                system("clear");
                printf("The data has been entered");
                printf("\n");
                getchar();
                getchar();
            }
            break;
        
        // Загрузка таблицы из файла
        case 2:
            free(note);
            note = load(filename, &size);
            break;

        // Сохранение табилцы в файл
        case 3:
            save(filename, note, size);
            break;

        // Вывод таблицы в консоль
        case 4:
            system("clear");
            outputData(note, size);
            printf("\n");
            getchar();
            getchar();
            break;

        // Редактирование записи в таблице
        case 5:
            system("clear");
            printf("Enter the record number: ");
            scanf(" %d", &numberRecord);
            if ((numberRecord <= size) && (numberRecord != 0))
                editData(note, numberRecord);
            break;

        // Удаление записи в таблице
        case 6:
            system("clear");
            printf("Enter the record number: ");
            scanf(" %d", &numberRecord);
            if ((numberRecord <= size) && (numberRecord != 0) && (size != 1)) //проверки перенести в функции
                deleteNote(note, numberRecord, &size);
            break;

        // Поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению
        case 7:
            system("clear");
            printf("Total viewers: %d" , findeNote(note, size));
            getchar();
            getchar();
            break;

        // Выход
        case 8:
            break;

        default:
            choise = 0;
            break;
        }

    }
    free(note);
    return 0;
}

void inputData(Cinema* note, int size)
{
    for (int i = 0; i < size; i++)
    {
        system("clear");

        printf("%d:\n", i + 1);
        
        getchar();
        printf("\nName of film: ");
        note[i].name = get_string();
        
        printf("\nhours, minutes, dd, mm: ");
        scanf("%d %d %d %d", &(note[i].hours), &(note[i].minutes), &(note[i].dd), &(note[i].mm));
        
        printf("\nPrice: ");
        scanf("%d", &(note[i].price));
        
        printf("\nViewers: ");
        scanf("%d", &(note[i].viewers));
    }
}

void outputData(Cinema* note, int size)
{
    system("clear");

    for (int i = 0; i < size; i++)
    {
        printf("\n%d:\n", i + 1);

        printf("Name of film: %s", note[i].name);

        printf("\nhours, minutes, dd, mm: %d %d %d %d", note[i].hours, note[i].minutes, note[i].dd, note[i].mm);

        printf("\nPrice: %d", note[i].price);

        printf("\nViewers: %d", note[i].viewers);

        printf("\n");
    }
}

void editData(Cinema* note, int numberRecord)
{
    system("cls");

    printf("%d:\n", numberRecord);

    delete note[numberRecord - 1].name;
    getchar();
    printf("Name of film: ");
    note[numberRecord - 1].name = get_string();

    printf("\nhours, minutes, dd, mm: ");
    scanf("%d %d %d %d", &(note[numberRecord - 1].hours), &(note[numberRecord - 1].minutes), &(note[numberRecord - 1].dd), &(note[numberRecord - 1].mm));
    
    printf("\nPrice: ");
    scanf("%d", &(note[numberRecord - 1].price));

    printf("Viewers: ");
    scanf("%d", &(note[numberRecord - 1].viewers));
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

void deleteNote(Cinema* note, int numberRecord, int* size)
{
    for (int i = numberRecord - 1; i < *size - 1; i++)
        note[i] = note[i + 1];
    note = (Cinema*)realloc(note, sizeof(Cinema) * (*size - 1));
    *size -= 1;
}

int findeNote(Cinema* note, int size)
{
    int viewers = 0;

    for (int i = 0; i < size; i++)
        viewers += note[i].viewers;

    return viewers;
}

int save(const char* filename, Cinema* p, int size)
{
    FILE* fp;
    
    if ((fp = fopen(filename, "wb+")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    
    fwrite(&size, sizeof(int), 1, fp);
    
    for (int i = 0; i < size; i++)
    {
        int nameSize = strlen(p[i].name);
        fwrite(&nameSize, sizeof(int), 1, fp);
        fwrite(p[i].name, sizeof(char), nameSize, fp);
        fwrite(&p[i].dd, sizeof(int), 1, fp);
        fwrite(&p[i].mm, sizeof(int), 1, fp);
        fwrite(&p[i].hours, sizeof(int), 1, fp);
        fwrite(&p[i].minutes, sizeof(int), 1, fp);
        fwrite(&p[i].price, sizeof(int), 1, fp);
        fwrite(&p[i].viewers, sizeof(int), 1, fp);
    }

    fclose(fp);
    return 0;
}

Cinema* load(const char* filename, int* sizeNote)
{
    FILE* fp;
    Cinema* note;

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        perror("Error occured while opening file");
        return NULL;
    }

    fread(sizeNote, sizeof(int), 1, fp);

    note = (Cinema*)malloc(sizeof(Cinema) * (*sizeNote));

    for (int i = 0; i < *sizeNote; i++) 
    {
        int nameSize;
        fread(&nameSize, sizeof(int), 1, fp);
        note[i].name = (char*)malloc(sizeof(char) * (nameSize + 1));
        note[i].name[nameSize] ='\0';
        fread(note[i].name, sizeof(char), nameSize, fp);
        fread(&note[i].dd, sizeof(int), 1, fp);
        fread(&note[i].mm, sizeof(int), 1, fp);
        fread(&note[i].hours, sizeof(int), 1, fp);
        fread(&note[i].minutes, sizeof(int), 1, fp);
        fread(&note[i].price, sizeof(int), 1, fp);
        fread(&note[i].viewers, sizeof(int), 1, fp);
    }

    fclose(fp);
    return note;
}