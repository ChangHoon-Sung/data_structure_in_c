#include <stdio.h>

int seq_search(int arr[], int len, int key) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int seq_search2(int arr[], int len, int key) {
    int i;
    arr[len] = key;
    for (i = 0; arr[i] != key; i++)
        ;
    if (i == len)
        return -1;
    else
        return i;
}

int binary_search(int arr[], int len, int key) {
    int s = 0, e = len, m;
    int cnt = 0;

    while (s <= e) {
        m = (s + e) / 2;
        if (arr[m] > key) {
            e = m - 1;
        } else if (arr[m] < key) {
            s = m + 1;
        } else {
            printf("탐색 횟수: %d\t", cnt);
            return m;
        }
        cnt++;
    }
    printf("탐색 횟수: %d\t", cnt);

    return -1;
}

int interpol_search(int arr[], int n, int key) {
    int low, high, j;
    int cnt = 0;

    low = 0;
    high = n - 1;
    while ((arr[high] >= key) && (key > arr[low])) {
        j = ((float)(key - arr[low]) / (arr[high] - arr[low]) * (high - low)) + low;
        if (key > arr[j]) {
            low = j + 1;
        } else if (key < arr[j]) {
            high = j - 1;
        } else {
            low = j;
        }
        cnt++;
    }

    printf("탐색 횟수: %d\t", cnt);
    if (arr[low] == key) {
        return low;
    } else {
        return -1;
    }
}