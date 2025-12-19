#ifndef TEST_H
#define TEST_H

void test_task_1(double* (*func)());
void test_insert_element(double* (*func)(double* ptr, int len, int index, double val));
void test_delete_element(double* (*func)(double* ptr, int len, int index));

#endif