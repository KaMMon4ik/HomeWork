#include <locale.h>
#include <stdio.h>

// ������� 7

void main() {

    setlocale(LC_ALL, "RUS");

    int n, sum = 0;

    printf("������� ����� N\n");
    scanf("%d", &n);

    while (n>0) {
        sum+=n%10;
        n/=10;
    }

    if (sum>9 && sum<100) {printf("����� ���� �������� ����������� ������");}
    else {printf("����� ���� �� �������� ����������� ������");}

}