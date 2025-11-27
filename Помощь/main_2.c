#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <time.h>

char* get_day_name(int n) {

    switch (n) {
        case 0: return "Понедельник";
        case 1: return "Вторник";
        case 2: return "Среда";
        case 3: return "Четверг";
        case 4: return "Пятница";
        case 5: return "Суббота";
        case 6: return "Воскресенье";
    }
    
}

char* get_month_name(int n) {

    switch (n) {
        case 0: return "Январь";
        case 1: return "Февраль";
        case 2: return "Март";
        case 3: return "Апрель";
        case 4: return "Май";
        case 5: return "Июнь";
        case 6: return "Июль";
        case 7: return "Август";
        case 8: return "Сентябрь";
        case 9: return "Октябрь";
        case 10: return "Ноябрь";
        case 11: return "Декабрь";
    }

}

void not_main() {

    setlocale(LC_ALL, "RUS");

    time_t t = time(NULL);

    struct tm *p;
    p = localtime(&t);

    printf("Московское время %02d:%02d:%02d\n", p->tm_hour, p->tm_min, p->tm_sec);

    printf("1. %s\n", get_day_name(p->tm_wday));
    printf("2. %02d.%02d.%d\n", p->tm_mday, p->tm_mon+1, p->tm_year+1900);
    printf("3. %02d %s\n", p->tm_mday, get_month_name(p->tm_mon));
    printf("4. Сегодня %d день %d года\n", p->tm_yday+1, p->tm_year+1900);

}
