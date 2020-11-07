#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/search.h"
#include "../include/tools.h"

#define N 3000000
#define DEBUG_FLAG 0

clock_t start, end;

int main(void) {
    int index[10] = {};
    int* array = random_array(N);
    int target = (array[0] * 91) % N;

    printf("Array: ");
    if (DEBUG_FLAG && N < 31) {
        print_array(array, N);
    } else {
        printf("generated!\n");
    }

    printf("Target: %d\n", target);

    printf("Sequential search ");
    start = clock();
    index[0] = seq_search(array, N, target);
    end = clock();
    printf("index: %d\t", index[0]);
    printf("perf: %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("Enhanced Sequential search ");
    start = clock();
    index[1] = seq_search2(array, N, target);
    end = clock();
    printf("index: %d\t", index[1]);
    printf("perf: %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);

    qsort(array, N, sizeof(int), compare);
    printf("ARRAY SORTED!\n");

    printf("Binary search ");
    start = clock();
    index[2] = binary_search(array, N, target);
    end = clock();
    printf("index: %d\t", index[2]);
    printf("perf: %lfs\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}