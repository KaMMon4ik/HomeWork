#include <locale.h>
#include <stdio.h>
#include <math.h>

// ������� 7

void main() {

    setlocale(LC_ALL, "RUS");

    double x, y, z, gamma;

    printf("������� x\n");
    scanf("%lf", &x);
    printf("������� y\n");
    scanf("%lf", &y);
    printf("������� z\n");
    scanf("%lf", &z);

    gamma=5*atan(x)-0.25*acos(x)*((x+3*fabs(x-y)+pow(x, 2))/(fabs(x-y)*z+pow(x, 2)));

    printf("��������� = %lf", gamma);

}