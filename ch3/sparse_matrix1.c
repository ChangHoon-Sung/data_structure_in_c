#include <stdio.h>

#define ROWS 3
#define COLS 3

void print_matrix(int a[ROWS][COLS])
{
    printf("-----\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    printf("-----\n");
}

void matrix_transpose(int a[ROWS][COLS], int b[ROWS][COLS])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            b[j][i] = a[i][j];
        }
    }
}

int main(void)
{
    int matrix_a[ROWS][COLS] = {{2, 3, 0}, {8, 9, 1}, {7, 0, 5}};
    int matrix_b[ROWS][COLS];

    print_matrix(matrix_a);
    matrix_transpose(matrix_a, matrix_b);
    print_matrix(matrix_b);
}