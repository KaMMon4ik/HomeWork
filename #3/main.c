#include <locale.h>
#include <stdio.h>

// ������� 7

void main() {

    setlocale(LC_ALL, "RUS");

    int s, t;

    printf("������� ���������� � ��\n");
    scanf("%d", &s);
    printf("������� ��������� ������� �� 1 ��\n");
    scanf("%d", &t);

    printf("��������� ������� ���������� %d ���", s*t);

}