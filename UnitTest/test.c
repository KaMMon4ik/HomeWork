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
	double elapsed_ms;

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

	puts("Началось тестирование задания #1");
	puts("--------------------------------\n");
	Sleep(1000);

	double total_time = 0;
	double total_cpu_time = 0;
	int total_memory = 0;
	bool free_check = false;

	for (int i=0; i<TEST_CNT; ++i) {
		
		int test_cnt = rand() % MAX_CNT_INPUT + 1;
		char test_str[4];
		_itoa(test_cnt, test_str, 10);

		QueryPerformanceFrequency(&frequency);
		GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
		size_t start_memory = pmc.PeakWorkingSetSize;
		QueryPerformanceCounter(&start_time);

		send_string(test_str);
		double* ans = func();

		double* full = calloc(test_cnt, sizeof(double));
		int cnt = 0;
		for (int j=0; j<test_cnt; ++j) {
			if (ans[j]==0) {cnt++;}
		}
		if (cnt==test_cnt) {free_check=true;}

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

void test_full_elements(double* (*func)(double *ptr, int len)) {

	puts("Началось тестирование");

	double ptr_1[10];
	double *result_1 = func(ptr_1, 10);

	if (result_1 != NULL) {
		printf("Первый тест прошёл\n");
		for (int i=0; i<10; ++i) {printf("%lf ", result_1[i]);}
	}

}