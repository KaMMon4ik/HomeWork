#define _CRT_SECURE_NO_WARNINGS

#include "test.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

extern double *full_elements(double *ptr, int len) {

	double* ptr_new = ptr;
	if (ptr_new == NULL || len <= 0) {return NULL;}
	for (int i=0; i<len; ++i) {ptr_new[i]=pow(i+1, 2)+sin(5*(i+1));}
	return ptr_new;

}

double *calc_elements(double *ptr, int len) {

	double* ptr_new = ptr;
	for (int i=0; i<len; ++i) {ptr_new[i]*=2;}
	return ptr_new;

}

void put_elements(double* ptr, int len) {

	for (int i = 0; i < len; ++i) { printf("%lf ", ptr[i]); }
	printf("\n");

}

double* task_1() {

	double* ptr_array;
	int len;
	puts("¬ведите длину массива: ");
	scanf("%d", &len);
	ptr_array = (double*) malloc(len * sizeof(double));
	if (ptr_array == NULL) {return 0;}

	full_elements(ptr_array, len);
	put_elements(ptr_array, len);
	ptr_array = calc_elements(ptr_array, len);
	put_elements(ptr_array, len);

	free(ptr_array);
	return ptr_array;

}

void main() {

	setlocale(LC_ALL, "RUS");

	test_task_1(task_1);

}