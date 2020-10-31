#include <stdio.h>
#include <time.h>

#include "../include/sort.h"
#include "../include/tools.h"

#define N 40
#define TEST_TYPE 1  // 1: 출력 비교, 2: 성능 비교

int main(void) {
    clock_t start, end;
    int *array = random_array(N);
    int *array1 = copy_array(array, N);
    int *array2 = copy_array(array, N);
    int *array3 = copy_array(array, N);
    int *array4 = copy_array(array, N);
    int *array5 = copy_array(array, N);
    int *comparison = copy_array(array, N);

    printf("Variable Sort Comparison\n\n");

    // unsorted
    if (TEST_TYPE == 2) {
        printf("원소 %d개의 정렬 성능을 비교합니다..", N);
    } else if (TEST_TYPE == 1 && N < 50) {
        printf("array\t");
        print_array(array, N);
    } else {
        printf("원소의 수를 50 미만으로 줄여주세요. (현재: %d)\n", N);
        exit(1);
    }
    printf("\n");

    printf("built-in sort");
    if (TEST_TYPE == 2) start = clock();
    built_in_quick_sort(comparison, N, sizeof(int), compare);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(comparison, N);

    printf("selection");
    if (TEST_TYPE == 2) start = clock();
    selection_sort(array, N);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array, N);

    printf("insertion");
    if (TEST_TYPE == 2) start = clock();
    insertion_sort(array1, N);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array1, N);

    printf("bubble\t");
    if (TEST_TYPE == 2) start = clock();
    bubble_sort(array2, N);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array2, N);

    printf("shell\t");
    if (TEST_TYPE == 2) start = clock();
    shell_sort(array3, N);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array3, N);

    printf("merge\t");
    if (TEST_TYPE == 2) start = clock();
    merge_sort(array4, 0, N - 1);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array4, N);

    printf("quick\t");
    if (TEST_TYPE == 2) start = clock();
    quick_sort(array5, 0, N - 1);
    if (TEST_TYPE == 2) {
        end = clock();
        printf(" takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    if (TEST_TYPE == 1) print_array(array5, N);

    return 0;
}