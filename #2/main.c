#include <locale.h>
#include <stdio.h>

// ������� 7

void main() {

    setlocale(LC_ALL, "RUS");

    int x;
    float v = 4*3;

    printf("������� ���������� � ��, ������� �������� �������\n");
    scanf("%d", &x);

    printf("������� �������� %d �� �� %.1f �", x, x/v);

}