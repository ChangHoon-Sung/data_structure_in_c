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

// A의 전치행렬 B 구하기
// 행과 열의 인덱스를 반대로 저장하면 된다.
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
    // 단순 이중 배열로 구현한 행렬
    // 구조는 단순하지만 희소행렬을 다룰 때 공간 낭비가 심하다.
    int matrix_a[ROWS][COLS] = {{2, 3, 0}, {8, 9, 1}, {7, 0, 5}};
    int matrix_b[ROWS][COLS];

    print_matrix(matrix_a);
    matrix_transpose(matrix_a, matrix_b);
    print_matrix(matrix_b);
}