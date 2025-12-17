#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

// Вариант 7

void send_string(char* str) {
	size_t len = strlen(str);
	INPUT* inputs = calloc((len + 1) * 2, sizeof(INPUT));

	for (int i = 0; i < len; ++i) {

		inputs[i * 2].type = INPUT_KEYBOARD;
		inputs[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
		inputs[i * 2].ki.wScan = str[i];

		inputs[i * 2 + 1].type = INPUT_KEYBOARD;
		inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_KEYUP;
		inputs[i * 2 + 1].ki.wScan = str[i];
	}

	SendInput((len + 1) * 2, inputs, sizeof(INPUT));
	free(inputs);
}

void main() {

    setlocale(LC_ALL, "RUS");
    
    double x, y, z, gamma;

    printf("Введите x\n");
    scanf("%lf", &x);
	send_string("555");
    printf("Введите y\n");
    scanf("%lf", &y);
    printf("Введите z\n");
    scanf("%lf", &z);

    gamma=5*atan(x)-0.25*acos(x)*((x+3*fabs(x-y)+pow(x, 2))/(fabs(x-y)*z+pow(x, 2)));

    printf("Результат = %lf", gamma);

}
