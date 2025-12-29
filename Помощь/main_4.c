#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct System {
    char name[50];
    char license[30];
    char size[20];
    char date[20];
    int commits;
    char language[20];
    char activity[20];
} System;

System systems[100];
int count = 0;

int random_number() {
    return rand() % 9 + 1;
}

void generate_license(char* license) {
    int first = rand() % 5 + 1;
    int second = rand() % 10;
    sprintf(license, "Лицензия %d.%d", first, second);
}

void generate_size(char* size) {
    int first = rand() % 101;
    int second = rand() % 10;
    sprintf(size, "%d.%d MB", first, second);
}

void generate_date(char* date) {
    int year = 2020 + rand() % 6;
    int month = rand() % 12 + 1;
    int day;
    if (month == 2) {
        day = rand() % 28 + 1;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = rand() % 30 + 1;
    }
    else {
        day = rand() % 31 + 1;
    }
    sprintf(date, "%d-%02d-%02d", year, month, day);
}

void generate_random() {
    if (count >= 100) {
        printf("База данных заполнена!\n");
        return;
    }

    printf("Сколько записей сгенерировать? ");
    int number;
    scanf("%d", &number);
    getchar();

    if (number <= 0) {
        printf("Ошибка: число должно быть положительным\n");
        return;
    }

    if (count + number > 100) {
        printf("Ошибка: можно добавить только %d записей\n", 100 - count);
        return;
    }

    for (int i = 0; i < number; i++) {
        int num = random_number();
        sprintf(systems[count].name, "Лабораторная %d", num);
        generate_license(systems[count].license);
        generate_size(systems[count].size);
        generate_date(systems[count].date);
        systems[count].commits = rand() % 51;
        char* languages[] = { "C", "C++", "Python", "Java", "JavaScript", "Go", "Rust" };
        strcpy(systems[count].language, languages[rand() % 7]);
        char* activities[] = { "Высокий", "Средний", "Низкий", "Неактивный" };
        strcpy(systems[count].activity, activities[rand() % 4]);
        count++;
    }

    printf("Сгенерировано %d записей\n", number);
}

void add_records() {
    if (count >= 100) {
        printf("База данных заполнена!\n");
        return;
    }

    printf("Добавление записи (все поля автоматические)\n");

    int num = random_number();
    sprintf(systems[count].name, "Лабораторная %d", num);
    printf("Название:     %s\n", systems[count].name);

    generate_license(systems[count].license);
    printf("Лицензия:     %s\n", systems[count].license);

    generate_size(systems[count].size);
    printf("Размер:       %s\n", systems[count].size);

    generate_date(systems[count].date);
    printf("Дата:         %s\n", systems[count].date);

    systems[count].commits = rand() % 51;
    printf("Коммиты:      %d\n", systems[count].commits);

    char* languages[] = { "C", "C++", "Python", "Java", "JavaScript", "Go", "Rust" };
    strcpy(systems[count].language, languages[rand() % 7]);
    printf("Язык:         %s\n", systems[count].language);

    char* activities[] = { "Высокий", "Средний", "Низкий", "Неактивный" };
    strcpy(systems[count].activity, activities[rand() % 4]);
    printf("Активность:   %s\n", systems[count].activity);

    count++;
    printf("Запись добавлена\n");
}

void show_all() {
    if (count == 0) {
        printf("Нет данных\n");
        return;
    }

    printf("Все системы (%d записей):\n", count);
    for (int i = 0; i < count; i++) {
        printf("\nСистема %d:\n", i + 1);
        printf("  Название: %s\n", systems[i].name);
        printf("  Лицензия: %s\n", systems[i].license);
        printf("  Размер: %s\n", systems[i].size);
        printf("  Дата: %s\n", systems[i].date);
        printf("  Коммиты: %d\n", systems[i].commits);
        printf("  Язык: %s\n", systems[i].language);
        printf("  Активность: %s\n", systems[i].activity);
    }
}
void menu() {
    printf("\nМеню:\n");
    printf("1. Показать все записи\n");
    printf("2. Добавить записи (авто)\n");
    printf("3. Сгенерировать записи\n");
    printf("4. Поиск по диапазону\n");
    printf("5. Сортировка данных\n");
    printf("6. Сохранить в файл\n");
    printf("7. Загрузить из файла\n");
    printf("0. Выход\n");
    printf("Выбор: ");
}

void main() {

    system("chcp 1251 > nul");
    srand(time(0));

    printf("Система управления данными\n");
    struct result;

    int choice;
    do {
        menu();
        scanf("%d", &choice);
        getchar();
        printf("\n");
        switch (choice) {
        case 1:
            show_all();
            break;
        case 2:
            add_records();
            break;
        case 3:
            generate_random();
            break;
        case 4:
            printf("В разработке\n");
            break;
        case 5:
            printf("В разработке\n");
            break;
        case 6:
            printf("В разработке\n");
            break;
        case 7:
            printf("В разработке\n");
            break;
        case 0:
            printf("Выход\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (choice!=0);

}