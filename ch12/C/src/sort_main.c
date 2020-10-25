#include <stdio.h>
#include <time.h>

#include "../include/sort.h"
#include "../include/tools.h"

#define N 10000
#define NUMBER_DEBUG 0

int main(void) {
    clock_t start, end;
    int *array = random_array(N);
    int *comparison = copy_array(array, N);

    printf("Variable Sort Comparison\n\n");

    printf("unsorted:");
    if (NUMBER_DEBUG)
        print_arrary(array, N);
    else
        printf(" generated!");
    printf("\n\n");

    printf("insertion");
    start = clock();
    selection_sort(array, N);
    end = clock();
    printf(" takes %lf seconds.\t", (double)(end - start) / CLOCKS_PER_SEC);
    if (NUMBER_DEBUG) print_arrary(array, N);
    printf("\n");

    printf("quicksort");
    start = clock();
    quick_sort(comparison, N, sizeof(int), compare);
    end = clock();
    printf(" takes %lf seconds.\t", (double)(end - start) / CLOCKS_PER_SEC);
    if (NUMBER_DEBUG) print_arrary(comparison, N);
    printf("\n");

    return 0;
}