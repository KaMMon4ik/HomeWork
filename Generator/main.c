#define _CRT_SECURE_NO_WARNINGS

#include "dirent.h"
#include <locale.h>
#include <stdio.h>
#include <string.h>

void main() {

	setlocale(LC_ALL, "RUS");

	DIR *programs = opendir("Programs");
    struct dirent *dir;

    FILE *includes = fopen("includes.h", "w");
    fprintf(includes, "#ifndef INCLUDES_H\n");
    fprintf(includes, "#define INCLUDES_H\n\n");

    int cnt = 0;
    while ((dir = readdir(programs)) != NULL) {
        if (strstr(dir->d_name, ".c")) {
            fprintf(includes, "#include \"%s\\%s\"\n", "Programs", dir->d_name);
            cnt++;
        }
    }
    closedir(programs);

    fprintf(includes, "\n#endif // INCLUDES_H");
    fclose(includes);

    printf("Создание заголовочного файла завершено. Подключено %d программа (-ы)\n", cnt);
    printf("Нажмите 'Enter', чтобы закрыть это окно ");
    getchar();

}