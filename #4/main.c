#include <locale.h>
#include <stdio.h>

// Вариант 7

void main() {

    setlocale(LC_ALL, "RUS");

    int a, b;

    printf("Введите сумму A\n");
    scanf("%d", &a);
    printf("Введите сумму B\n");
    scanf("%d", &b);

    if (a%2==0^b%2==0) {printf("Код успешно сгенерирован");}
    else {printf("Код не сгенерирован");}

}