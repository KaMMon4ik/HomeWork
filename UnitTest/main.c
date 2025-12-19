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

	for (int i = 0; i < len; ++i) { printf("%lf ", ptr[i]); }
	printf("\n");

}

//double* insert(double* ptr, int len, int index, double val) {
//    // Проверяем корректность позиции
//    if (position < 0 || position > size) {
//        printf("Ошибка: неверная позиция для вставки\n");
//        return arr;
//    }
//
//    // Создаем новый массив на один элемент больше
//    int* newArr = (int*)malloc((size + 1) * sizeof(int));
//
//    // Копируем элементы до позиции вставки
//    for (int i = 0; i < position; i++) {
//        newArr[i] = arr[i];
//    }
//
//    // Вставляем новый элемент
//    newArr[position] = element;
//
//    // Копируем оставшиеся элементы
//    for (int i = position; i < size; i++) {
//        newArr[i + 1] = arr[i];
//    }
//
//    // Освобождаем память старого массива
//    free(arr);
//
//    return newArr;
//}

int delete_k (double* ptr_arr, int size, int k) {

    int n = size-1;
	for (int i=k; i<(size-1); i++) ptr_arr[i] = ptr_arr[i+1];
    return n;

}

double* task_1() {

	double* ptr;
	int len;
	puts("Введите длину массива: ");
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
	
	test_insert(in)

}