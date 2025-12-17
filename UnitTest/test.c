#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <psapi.h>

void send_string(char* str) {
	size_t len = strlen(str);
	INPUT* inputs = calloc((len+1)*2, sizeof(INPUT));

	for (int i=0; i<=len; ++i) {
		inputs[i*2].type = INPUT_KEYBOARD;
		inputs[i*2].ki.dwFlags = KEYEVENTF_UNICODE;
		if (i==len) inputs[i*2].ki.wScan = VK_RETURN;
		else inputs[i*2].ki.wScan = str[i];

		inputs[i*2+1].type = INPUT_KEYBOARD;
		inputs[i*2+1].ki.dwFlags = KEYEVENTF_KEYUP;
		if (i==len) inputs[i*2+1].ki.wScan = VK_RETURN;
		else inputs[i*2+1].ki.wScan = str[i];
	}

	SendInput((len+1)*2, inputs, sizeof(INPUT));
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

	char str[100];
	int test_cnt = 75;
	_itoa(test_cnt, str, 10);

	QueryPerformanceFrequency(&frequency);
	GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
	size_t start_memory = pmc.PeakWorkingSetSize;
	QueryPerformanceCounter(&start_time);
	send_string(str);
	double* ans = func();
	QueryPerformanceCounter(&end_time);
	GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
	size_t end_memory = pmc.PeakWorkingSetSize;

	elapsed_ms = (double) (end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart;

	puts("\n--------------------------------\n");
	Sleep(1000);
	printf("- Потрачено памяти: %u байт\n", (unsigned) (end_memory - start_memory) / 1024);
	printf("- Функция выполнялась: %.3f сек\n", elapsed_ms);

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