#include <locale.h>
#include <stdio.h>

// Вариант 7

void main() {

    setlocale(LC_ALL, "RUS");

    int x;
    float v = 4 * 3;

    printf("Введите расстояние в км, которое пробежал мальчик\n");
    scanf("%d", &x);

    printf("Мальчик пробежал %d км за %.1f ч", x, x / v);

}