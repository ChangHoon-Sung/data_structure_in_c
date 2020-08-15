#include <stdio.h>

#define MAX_TERMS 101

// 새로운 행렬 구조체의 원소 구조체
typedef struct
{
    int row;
    int col;
    int value;
} element;

// 새로운 행렬 구조체
// 단순 이중 배열보다는 복잡하지만 공간 효율이 높음
typedef struct
{
    element data[MAX_TERMS];
    int rows;
    int cols;
    int terms;
} SparseMatrix;

void print_matrix(SparseMatrix a)
{
    printf("=========\n");
    for (int i = 0; i < a.terms; i++)
        printf("(%d, %d, %d)\n", a.data[i].row, a.data[i].col, a.data[i].value);
    printf("=========\n");
}

// 새로운 행렬 구조체의 전치행렬 구하기
// 시간복잡도 O(COLS * N)
SparseMatrix matrix_transpose2(SparseMatrix a)
{
    int bindex = 0;
    SparseMatrix b;
    b.rows = a.rows;
    b.cols = a.cols;
    b.terms = a.terms;

    // 전치행렬을 정렬하기 위해 열의 값이 0인 행부터 이동
    for (int c = 0; c < a.cols; c++)
    {
        for (int i = 0; i < a.terms; i++)
        {
            if (a.data[i].col == c)
            {
                b.data[bindex].row = a.data[i].col;
                b.data[bindex].col = a.data[i].row;
                b.data[bindex].value = a.data[i].value;
                bindex++;
            }
        }
    }
    return b;
}

int main(void)
{
    SparseMatrix a = {
        {{0, 1, 9},
         {1, 5, 8},
         {3, 0, 6},
         {3, 0, 7},
         {3, 1, 5},
         {4, 5, 1},
         {5, 2, 2}},
        6,
        6,
        7,
    };
    SparseMatrix b;

    print_matrix(a);

    b = matrix_transpose2(a);

    print_matrix(b);

    return 0;
}