#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

// 시간복잡도: O(N)
void insert(int arr[], int value, int loc)
{
    for (int i = N - 2; i >= loc; i--)
        arr[i + 1] = arr[i];

    arr[loc] = value;
}

// 시간복잡도: O(N)
void delete (int arr[], int value, int loc)
{
    for (int i = loc; i < N - 1; i++)
        arr[i] = arr[i + 1];

    arr[N - 1] = 0;
}

void print_array(int arr[])
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    int loc = 0;
    int *arr = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N - 1; i++)
        arr[i] = i + 1;

    printf("Original Function: ");
    print_array(arr);

    printf("Insert Tested: ");
    insert(arr, -1, loc);
    print_array(arr);

    printf("Delete Tested: ");
    delete (arr, -1, loc);
    print_array(arr);

    return 0;
}