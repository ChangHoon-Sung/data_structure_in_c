#include <stdio.h>

#define ROWS 3
#define COLS 3
int matrix[3][3] = {{2, 3, 0}, {8, 9, 1}, {7, 0, 5}};

void print_matrix()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_transpose()
{
    int tmp;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < i; j++)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
        printf("\n");
    }
}

int main(void)
{
    print_matrix();
    matrix_transpose();
    print_matrix();
}