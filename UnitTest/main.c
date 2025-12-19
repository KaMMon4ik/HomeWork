#define _CRT_SECURE_NO_WARNINGS

#include "test.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

	for (int i=0; i<len; ++i) {printf("%lf ", ptr[i]);}
	printf("\n");

}

double* insert_element(double* ptr, int len, int index, double val) {

    double* newPtr = malloc((len+1)*sizeof(double));

    for (int i=0; i<index; ++i) {newPtr[i] = ptr[i];}
    newPtr[index] = val;
    for (int i=index; i<len; ++i) {newPtr[i+1] = ptr[i];}

    return newPtr;
}

double* delete_element(double* ptr, int len, int index) {

	double* newPtr = malloc((len-1)*sizeof(double));

	for (int i=0; i<index; ++i) {newPtr[i] = ptr[i];}
	for (int i=index; i<(len-1); ++i) {newPtr[i] = ptr[i+1];}

    return newPtr;

}

double* task_1() {

	double* ptr;
	int len;
	puts("¬ведите длину массива: ");
	scanf("%d", &len);
	ptr = (double*) malloc(len*sizeof(double));
	if (ptr==NULL) {return 0;}

	full_elements(ptr, len);
	put_elements(ptr, len);
	ptr = calc_elements(ptr, len);
	put_elements(ptr, len);

	free(ptr);

	return ptr;

}

void main() {

	setlocale(LC_ALL, "RUS");

	//test_task_1(task_1);
	
	test_insert_element(insert_element);

	//test_delete_element(delete_element);

}