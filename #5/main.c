#include <locale.h>
#include <stdio.h>
#include <math.h>

// Вариант 7

void main() {

    setlocale(LC_ALL, "RUS");
    
    double x, y, z, gamma;

    printf("Введите x\n");
    scanf("%lf", &x);
    printf("Введите y\n");
    scanf("%lf", &y);
    printf("Введите z\n");
    scanf("%lf", &z);

    gamma=5*atan(x)-0.25*acos(x)*((x+3*fabs(x-y)+pow(x, 2))/(fabs(x-y)*z+pow(x, 2)));

    printf("Результат = %lf", gamma);

}
