#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <math.h>
#include <setjmp.h>
#include <stdbool.h>

int TEST_CNT = 10;
int MAX_CNT_INPUT = 100;

void send_string(char* str) {
	size_t len = strlen(str);
	INPUT* inputs = calloc(len+1, sizeof(INPUT));
	if (inputs == NULL) {
		puts("Ошибка выделения памяти при имитации нажатий клавиш");
		return -1;
	}

	for (int i=0; i<len; ++i) {
		inputs[i].type = INPUT_KEYBOARD;
		inputs[i].ki.dwFlags = KEYEVENTF_UNICODE;
		inputs[i].ki.wScan = str[i];
	}

	inputs[len].type = INPUT_KEYBOARD;
	inputs[len].ki.dwFlags = KEYEVENTF_UNICODE;
	inputs[len].ki.wScan = VK_RETURN;

	SendInput(len+1, inputs, sizeof(INPUT));
	free(inputs);
}

void test_task_1(double* (*func)()) {

	HANDLE process;
	PROCESS_MEMORY_COUNTERS pmc;
	LARGE_INTEGER start_time, end_time, frequency;

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

	puts("Началось тестирование задания #1");
	puts("--------------------------------\n");
	Sleep(1000);

	double total_time = 0;
	int total_memory = 0;
	bool free_check = false;

	srand(time(0));

	for (int i=0; i<TEST_CNT; ++i) {

		int test_len = rand() % MAX_CNT_INPUT + 1;
		char test_str[4];
		_itoa(test_len, test_str, 10);

		QueryPerformanceFrequency(&frequency);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t start_memory = pmc.PeakWorkingSetSize;
		QueryPerformanceCounter(&start_time);

		send_string(test_str);
		double* ans = func();

		double* full = calloc(test_len, sizeof(double));
		int cnt = 0;
		for (int j=0; j<test_len; ++j) {
			if (ans[j]==0) {cnt++;}
		}
		if (cnt==test_len) {free_check=true;}

		QueryPerformanceCounter(&end_time);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t end_memory = pmc.PeakWorkingSetSize;

		total_memory += end_memory-start_memory;
		total_time += (double) (end_time.QuadPart-start_time.QuadPart) / frequency.QuadPart;
		puts("\n--------------------------------\n");

	}

	Sleep(1000);
	printf("- Среднее количество потраченной памяти: %d байт\n", total_memory/TEST_CNT);
	printf("- Среднее время выполнения функции: %.3f сек\n", total_time/TEST_CNT);
	printf("- Выделенная память %sбыла освобождена\n", free_check==true ? "" : "НЕ ");

}

void test_insert_element(double* (*func)(double* ptr, int len, int index, double val)) {
	
	HANDLE process;
	PROCESS_MEMORY_COUNTERS pmc;
	LARGE_INTEGER start_time, end_time, frequency;

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

	puts("Началось тестирование вставки элемента в массив");
	puts("-----------------------------------------------\n");
	Sleep(1000);

	double total_time = 0;
	int total_memory = 0;
	int errors = 0;

	srand(time(0));

	for (int i=0; i<TEST_CNT; ++i) {

		int test_len = rand() % MAX_CNT_INPUT + 1;
		int test_index = rand() % test_len;
		double test_val = (double) (rand()%(rand()+1)) / (rand()%(rand()+1)) - (rand()%(rand()+1)) + (rand()%(rand()+1));

		printf("Тест #%d | Длина массива: %d | Индекс вставки: %d | Значение для вставки: %lf\n", i+1, test_len, test_index, test_val);

		QueryPerformanceFrequency(&frequency);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t start_memory = pmc.PeakWorkingSetSize;
		QueryPerformanceCounter(&start_time);

		double* ptr = calloc(test_len, sizeof(double));
		double* ans = func(ptr, test_len, test_index, test_val);

		int cnt = 0;
		for (int j=0; j<=test_len; ++j) {
			if (ans[j]==0) {cnt++;}
		}
		if (cnt!=test_len || ans[test_index]!=test_val) {
			errors+=1;
			if (cnt!=test_len) printf("- Ошибка: длина массива не увеличилась\n");
			else printf("- Ошибка: элемент не был вставлен на данный индекс\n");
		}

		QueryPerformanceCounter(&end_time);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t end_memory = pmc.PeakWorkingSetSize;

		free(ptr);
		free(ans);

		total_memory += end_memory - start_memory;
		total_time += (double) (end_time.QuadPart-start_time.QuadPart) / frequency.QuadPart;
		puts("\n-----------------------------------------------\n");

	}

	Sleep(1000);
	printf("- Среднее количество потраченной памяти: %d байт\n", total_memory / TEST_CNT);
	printf("- Среднее время выполнения функции: %.3f сек\n", total_time / TEST_CNT);
	printf("- Ошибок при выполении тестов: %d\n", errors);

}

void test_delete_element(double* (*func)(double* ptr, int len, int index)) {

	HANDLE process;
	PROCESS_MEMORY_COUNTERS pmc;
	LARGE_INTEGER start_time, end_time, frequency;

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

	puts("Началось тестирование удаления элемента из массив");
	puts("-------------------------------------------------\n");
	Sleep(1000);

	double total_time = 0;
	int total_memory = 0;
	int errors = 0;

	srand(time(0));

	for (int i=0; i<TEST_CNT; ++i) {

		int test_len = rand() % MAX_CNT_INPUT + 1;
		int test_index = rand() % test_len;

		printf("Тест #%d | Длина массива: %d | Индекс удаления: %d\n", i+1, test_len, test_index);

		QueryPerformanceFrequency(&frequency);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t start_memory = pmc.PeakWorkingSetSize;
		QueryPerformanceCounter(&start_time);

		double* ptr = malloc(test_len*sizeof(double));
		for (int j=0; j<test_len; ++j) {ptr[j] = (double) (rand()%(rand()+1)) / (rand()%(rand()+1)) - (rand()%(rand()+1)) + (rand()%(rand()+1));}
		double* ans = func(ptr, test_len, test_index);

		int cnt = 0;
		for (int j=0; j<test_index; ++j) {
			if (ans[j]==ptr[j]) {cnt++;}
		}
		for (int j=test_index; j<test_len-1; ++j) {
			if (ans[j]==ptr[j+1]) {cnt++;}
		}
		if (cnt!=test_len-1) {
			errors += 1;
			printf("- Ошибка: элемент не был удален %d\n", cnt);
		}

		QueryPerformanceCounter(&end_time);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t end_memory = pmc.PeakWorkingSetSize;

		free(ptr);
		free(ans);

		total_memory += end_memory - start_memory;
		total_time += (double)(end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;
		puts("\n-------------------------------------------------\n");

	}

	Sleep(1000);
	printf("- Среднее количество потраченной памяти: %d байт\n", total_memory / TEST_CNT);
	printf("- Среднее время выполнения функции: %.3f сек\n", total_time / TEST_CNT);
	printf("- Ошибок при выполении тестов: %d\n", errors);

}