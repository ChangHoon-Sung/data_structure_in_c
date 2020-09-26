#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 200

typedef int element;
typedef struct Heap {
    element heap[MAX_ELEMENT];
    int heap_size;
} Heap;

Heap* create_heap() {
    return (Heap*)malloc(sizeof(Heap));
}

void init(Heap* h) {
    h->heap_size = 0;
}

void insert_max_heap(Heap* h, element item) {
    int i = ++(h->heap_size);

    while (i != 1 && item > h->heap[i / 2]) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

element delete_max_heap(Heap* h) {
    element item = h->heap[1];
    element temp = h->heap[(h->heap_size)--];

    int parent = 1, child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child] < h->heap[child + 1]) {
            child++;
        }
        if (temp > h->heap[child]) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

int* heap_sort(int input[], int n) {
    Heap h;
    int* result = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        insert_max_heap(&h, input[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        result[i] = delete_max_heap(&h);
    }
    return result;
}

int main(void) {
    int input[10] = {3, 12, 32, 46, 7, 1, 4, 5, 100, 72};
    int* sorted = NULL;

    clock_t start = clock();
    sorted = heap_sort(input, 10);
    clock_t end = clock();
    printf("HeapSort with 10 elements takes %lf seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

    for (int i = 0; i < 10; i++) {
        printf("[%d] ", sorted[i]);
    }
    printf("\n");

    return 0;
}