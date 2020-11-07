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
    printf("\n");
}

int *copy_array(int *arr, int len) {
    int *temp = (int *)malloc(sizeof(int) * len);
    memcpy(temp, arr, sizeof(int) * len);
    return temp;
}
