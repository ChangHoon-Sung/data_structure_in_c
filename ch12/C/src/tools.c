#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a > *(int *)b) ? 1 : (*(int *)a < *(int *)b ? -1 : 0);
}

int *random_array(int len) {
    srand(time(NULL));
    int *arr = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        arr[i] = random() % len;
    }
    return arr;
}

void print_array(int *arr, int len, int perf_time) {
    printf("\t");
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int *copy_array(int *arr, int len) {
    int *temp = (int *)malloc(sizeof(int) * len);
    memcpy(temp, arr, sizeof(int) * len);
    return temp;
}

int is_equal(int *arr1, int *arr2, int len) {
    int result = 1;
    for (int i = 0; i < len; i++) {
        if (arr1[i] != arr2[i]) {
            printf("test fail! index: %d, arr1[%d]: %d, arr2[%d]: %d", i, arr1[i], arr2[i]);
            result = 0;
            break;
        }
    }

    return result;
}