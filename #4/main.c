#include <locale.h>
#include <stdio.h>

// ������� 7

void main() {

    setlocale(LC_ALL, "RUS");

    int a, b;

    printf("������� ����� A\n");
    scanf("%d", &a);
    printf("������� ����� B\n");
    scanf("%d", &b);

    if (a%2==0^b%2==0) {printf("��� ������� ������������");}
    else {printf("��� �� ������������");}

}