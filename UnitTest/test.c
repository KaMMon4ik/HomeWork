#include <stdio.h>
#include <Windows.h>
#include <psapi.h>

void test_task_1(void (*func)()) {

	HANDLE process;
	PROCESS_MEMORY_COUNTERS pmc;
	LARGE_INTEGER start_time, end_time, frequency;

	QueryPerformanceFrequency(&frequency);

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	if (process == NULL) {
		printf("Ошибка при получении хэндла процесса\n");
		return;
	}

	puts("Началось тестирование задания 1");

	GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
	unsigned int start_memory = pmc.PeakWorkingSetSize;
	QueryPerformanceCounter(&start_time);
	func();
	QueryPerformanceCounter(&end_time);
	GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
	unsigned int end_memory = pmc.PeakWorkingSetSize;

	printf("Потрачено памяти: %u байт\n", (end_memory - start_memory) / 1024);
	printf("Функция выполнялась: %f сек\n", (double) (end_time.QuadPart - start_time.QuadPart) / frequency.QuadPart / 1000);

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