#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <stdio.h>
#include <math.h>

struct point {
    float x;
    float y;
    char name;
};

typedef struct point Point;

void put_point(Point z) {printf("Point %c (%.1f; %.1f)\n", z.name, z.x, z.y);}

float get_points_dist(Point z, Point w) {return sqrtf(pow(w.x-z.x, 2)+pow(w.y-z.y, 2));}

Point get_middle_point(Point z, Point w) {

    Point m;
    m.name = 'm';
    m.x = (z.x+w.x)/2;
    m.y = (z.y+w.y)/2;
    return m;

}

void not_not_main() {

    setlocale(LC_ALL, "RUS");

    Point a, b;

    printf("Введите название точки A: ");
    scanf("%c", &a.name);
    printf("Введите координаты x y точки A через пробел: ");
    scanf("%f %f", &a.x, &a.y);

    getchar();

    printf("Введите название точки B: ");
    scanf("%c", &b.name);
    printf("Введите координаты x y точки B через пробел: ");
    scanf("%f %f", &b.x, &b.y);

    Point m = get_middle_point(a, b);
    put_point(m);

}
