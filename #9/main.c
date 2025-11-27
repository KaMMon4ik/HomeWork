#define _CRT_SECURE_NO_WARNINGS
#define swap(a, b) (a ^= b ^= a ^= b)

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

// ¬ариант 19

void main() {

    setlocale(LC_ALL, "RUS");

    char print_char;
    int b_x, b_y, c_x, c_y, d_x, d_y;

    printf("¬ведите символ, из которого будет состо€ть фигура:\n");
    scanf("%c", &print_char);
    printf("¬ведите координаты точки B через пробел:\n");
    scanf("%d %d", &b_x, &b_y);
    printf("¬ведите координаты точки C через пробел:\n");
    scanf("%d %d", &c_x, &c_y);
    printf("¬ведите координаты точки D через пробел:\n");
    scanf("%d %d", &d_x, &d_y);

    int a[2] = {0, 0};
    int b[2] = {b_x, b_y};
    int c[2] = {c_x, c_y};
    int d[2] = {d_x, d_y};

    int rows = max(max(a[1], b[1]), max(c[1], d[1]))-min(min(a[1], b[1]), min(c[1], d[1]))+3;
    int columns = max(max(a[0], b[0]), max(c[0], d[0]))+3;
    int *data = malloc((size_t) rows*columns*sizeof(int));
    int **matrix = malloc((size_t) rows*sizeof(int*));

    for (int i=0; i<rows; ++i) {matrix[i]=data+i*columns;}
    
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<columns; ++j) {matrix[i][j] = 0;}
    }

    int start_x = max(max(a[1], b[1]), max(c[1], d[1]))+1;

    int x0, y0;
    int x1, y1;

    for (int k=0; k<4; ++k) {
        switch (k) {
            case 0: x0 = 0, x1 = b[0], y0 = 0, y1 = b[1]; break;
            case 1: x0 = b[0], x1 = c[0], y0 = b[1], y1 = c[1]; break;
            case 2: x0 = c[0], x1 = d[0], y0 = c[1], y1 = d[1]; break;
            case 3: x0 = d[0], x1 = a[0], y0 = d[1], y1 = a[1]; break;
        }
        matrix[start_x-y0][x0+1] = 1;
        matrix[start_x-y1][x1+1] = 1;
        if (abs(y1-y0)<=abs(x1-x0)) {
            if (x0>x1) {
                swap(x0, x1);
                swap(y0, y1);
            }
            while (x0<x1) {
                double error = (double) (y1-y0)/(x1-x0);
                if (error>=0.725) {y0 += 1;}
                if (error<=-0.5) {y0 -= 1;}
                x0 += 1;
                matrix[start_x-y0][x0+1] = 1;
            }
        }
        else {
            if (y0>y1) {
                swap(x0, x1);
                swap(y0, y1);
            }
            while (y0<y1) {
                double error = (double) (x1-x0)/(y1-y0);
                if (error<=-0.275) {x0 -= 1;}
                if (error>=0.5) {x0 += 1;}
                y0 += 1;
                matrix[start_x-y0][x0+1] = 1;
            }
        }
    }

    for (int i=0; i<rows; ++i) {
        printf("\n");
        for (int j=0; j<columns; ++j) {
            if (matrix[i][j]==1) {printf("%c ", print_char);}
            else {printf("  ");}
        }
    }

}