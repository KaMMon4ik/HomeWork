#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define MAX_BOOKS 100

typedef struct {
    char title[40];
    char author[40];
    int  year;
    char genre[20];
    int  pages;
} Book;

int printTable(Book* a, int n) {
    int i;
    if (n <= 0) {
        printf("Список пуст.\n");
        return 0;
    }
    printf("\n-----------------------------------------------------------------------------------\n");
    printf("| %-3s | %-24s | %-14s | %-6s | %-12s | %-5s |\n", "№", "Название", "Автор", "Год", "Жанр", "Стр.");
    printf("-----------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("| %-3d | %-24s | %-14s | %-6d | %-12s | %-5d |\n", i + 1, a[i].title, a[i].author, a[i].year, a[i].genre, a[i].pages);
    }
    printf("-----------------------------------------------------------------------------------\n");
    return 0;
}

int loadFromFile(char* fname, Book* a, int max) {
    FILE* f = fopen(fname, "r");
    char line[256];
    int count = 0;
    if (!f) {
        printf("Не удалось открыть файл.\n");
        return count;
    }
    while (fgets(line, sizeof(line), f) && count < max) {
        Book b;
        if (sscanf(line, "%39[^;];%39[^;];%d;%19[^;];%d", b.title, b.author, &b.year, b.genre, &b.pages) == 5) {
            a[count++] = b;
        }
    }
    fclose(f);
    return count;
}

int saveToFile(char* fname, Book* a, int n) {
    FILE* f = fopen(fname, "w");
    int i;
    if (!f) {
        printf("Не удалось открыть файл для записи.\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        fprintf(f, "%s;%s;%d;%s;%d\n", a[i].title, a[i].author, a[i].year, a[i].genre, a[i].pages);
    fclose(f);
    printf("Сохранено %d записей.\n", n);
    return n;
}

Book* addBook(Book* a, int* n, int max) {
    if (*n >= max) {
        printf("Массив переполнен.\n");
        return a;
    }
    Book b;
    printf("Введите данные книги (без пробелов, вместо них _):\n");
    printf("Название: ");  scanf("%39s", b.title);
    printf("Автор: ");     scanf("%39s", b.author);
    printf("Год: ");       scanf("%d", &b.year);
    printf("Жанр: ");      scanf("%19s", b.genre);
    printf("Страниц: ");   scanf("%d", &b.pages);
    a[*n] = b;
    (*n)++;

    char choice;
    printf("\nДобавить книгу в файл? (да/нет): ");
    scanf(" %c", &choice);

    if (choice == 'да' || choice == 'нет') {
        char filename[64];
        printf("Введите имя файла: ");
        scanf("%63s", filename);
        FILE* f = fopen(filename, "a");
        if (f) {
            fprintf(f, "%s;%s;%d;%s;%d\n", b.title, b.author, b.year, b.genre, b.pages);
            fclose(f);
            printf("Книга добавлена в файл '%s'\n", filename);
        }
        else {
            printf("Не удалось открыть файл для записи.\n");
        }
    }
    return a;
}

Book* sortByYear(Book* a, int n) {
    Book* result = (Book*) malloc(MAX_BOOKS * sizeof(Book));
    memcpy(result, a, MAX_BOOKS * sizeof(Book));
    for (int i = 1; i < n; i++) {
        Book key = result[i];
        int j = i - 1;
        while (j >= 0 && result[j].year > key.year) {
            result[j+1] = result[j];
            j--;
        }
        result[j+1] = key;
    }
    return result;
}
//вывод строки
int searchOne(Book* a, int n, char* author) {
    Book* result = (Book*)malloc(MAX_BOOKS * sizeof(Book));
    memcpy(result, a, MAX_BOOKS * sizeof(Book));
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(a[i].author, author) == 0) {
            result[k++] = a[i];
        }
    }
    if (k) printTable(result, k);
    free(result);
    return k;
}

int searchTwo(Book* a, int n, char* author, int year) {
    Book* result = (Book*)malloc(MAX_BOOKS * sizeof(Book));
    memcpy(result, a, MAX_BOOKS * sizeof(Book));
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(a[i].author, author) == 0 && a[i].year == year) {
            result[k++] = a[i];
        }
    }
    if (k) printTable(result, k);
    free(result);
    return k;
}

int nott_main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");
    Book books[MAX_BOOKS] = {
        {"Мастер_и_Маргарита", "Булгаков",    1967, "Роман",       480},
        {"Идиот",              "Достоевский", 1869, "Роман",       640},
        {"Пикник_на_обочине",  "Стругацкие",  1972, "Фантастика",  300},
        {"Вий",                "Гоголь",      1835, "Мистика",     210},
        {"Тарзан",             "Берроуз",     1912, "Приключения", 290}
    };
    int size = 5;
    int choice;
    char fname[64];

    while (1) {
        printf("\n----- БИБЛИОТЕКА КНИГ -----\n");
        printf("1. Показать имеющиеся книги\n");
        printf("2. Загрузить книги из файла\n");
        printf("3. Сохранить книги в файл\n");
        printf("4. Добавить книгу\n");
        printf("5. Отсортировать книги по году\n");
        printf("6. Поиск книги по автору\n");
        printf("7. Поиск книги по автору и году\n");
        printf("0. Выход\nВаш выбор: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 0) break;
        switch (choice) {
        case 1:
            printTable(books, size);
            break;
        case 2:
            printf("Имя файла для чтения: ");
            scanf("%63s", fname);
            size = loadFromFile(fname, books, MAX_BOOKS);
            printf("Загружено записей: %d\n", size);
            break;
        case 3:
            printf("Имя файла для записи: ");
            scanf("%63s", fname);
            saveToFile(fname, books, size);
            break;
        case 4: {
            Book* result = addBook(books, &size, MAX_BOOKS);
            if (result) {
                printf("\nТаблица книг с добавленной книгой:\n");
                printTable(books, size);
            }
            break;
        }
        case 5: {
            Book* result = sortByYear(books, size);
            printf("Отсортировано по году.\n");
            printTable(result, size);
            free(result);
            break;
        }
        case 6: {
            char author[40];
            printf("Введите автора (без пробелов, как в таблице): ");
            scanf("%39s", &author);
            int result_size = searchOne(books, size, author);
            if (result_size == 0) printf("Ничего не найдено.\n");
            break;
        }
        case 7: {
            char author[40];
            int year;
            printf("Введите автора: ");
            scanf("%39s", &author);
            printf("Введите год: ");
            scanf("%d", &year);
            int result_size = searchTwo(books, size, author, year);
            if (result_size == 0) printf("Ничего не найдено.\n");
            break;
        }
        default:
            printf("Неверный пункт меню.\n");
        }
    }
    return 0;
}