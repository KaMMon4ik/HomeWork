#include <stdio.h>

void test_task_1(void (*func)()) {

	puts("Началось тестирование");

	func();

}

void test_full_elements(double* (*func)(double *ptr, int len)) {

	puts("Началось тестирование");

	double ptr_1[10];
	double *result_1 = func(ptr_1, 10);

	if (result_1 != NULL) {
		printf("Первый тест прошёл\n");
		for (int i=0; i<10; ++i) {printf("%lf ", result_1[i]);}
	}

}