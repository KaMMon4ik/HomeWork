#define _CRT_SECURE_NO_WARNINGS

#include "includes.h"
#include "dirent.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char *filename;
    int variant;
    void (*function)();
    void *result;
} TestInfo;

TestInfo *tests;
int cnt = 0;

void add_test(char* file_name, int variant, void* (*func)(), void *result) {
    tests = realloc(tests, sizeof(TestInfo)*(++cnt+1));
    tests[cnt-1].filename = file_name;
    tests[cnt-1].variant = variant;
    tests[cnt-1].function = func;
    tests[cnt-1].result = result;
}

void main() {

    setlocale(LC_ALL, "RUS");

    //DIR* programs = opendir("Programs");
    //struct dirent* dir;

    //char func_name[256];
    //strncpy(func_name, dir->d_name, strlen(dir->d_name) - 2);
    //strcat(func_name, "_Вариант");
    //void* (*func)() = dlsym
    //    //function func_name(2, 3);
    //    printf("%s\n", func_name);

    //while ((dir = readdir(programs)) != NULL) {
    //    if (strstr(dir->d_name, ".c")) {
    //        add_test(dir->d_name, )
    //    }
    //}
    //closedir(programs);

    add_test("123.c", 3, add_test, add_test);
    printf("%s\n", tests[0].filename);

    int var = Латышев_Арсений_бТИИ_251_Вариант();

    getchar();

}