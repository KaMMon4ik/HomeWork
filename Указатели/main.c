#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void main() {

    setlocale(LC_ALL, "RUS");

    int row = 2;
    int column = 3;

    int *data = malloc(row*column*sizeof(int));
    int **matrix = malloc(row*sizeof(int*));

    if (matrix==NULL || data==NULL) {return;}

    for (int i=0; i<row; ++i) matrix[i]=data+i*column;

    matrix[0][0] = 123;
    
    for (int i=0; i<row; ++i) {
        for (int j=0; j<column; ++j) printf("%d ", matrix[i][j]);
        printf("\n");
    }

}