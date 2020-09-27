#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000

typedef struct Heap {
    int heap[MAX_SIZE + 1];
    int heap_size;
} Heap;

Heap *create_heap(void) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->heap_size = 0;
    return heap;
}

void insert_max_heap(Heap *h, int item) {
    int i = ++h->heap_size;

    while (i != 1 && item > h->heap[i / 2]) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

void print_inputay(int input[]) {
    for (int i = 1; i < MAX_SIZE + 1; i++) {
        printf("[%d] ", input[i]);
    }
}

void heapify(int *heap, int idx, int heap_size) {
    int temp;
    int largest = idx;
    int left_child = idx * 2, right_child = idx * 2 + 1;

    if (left_child <= heap_size && heap[left_child] > heap[largest]) {
        largest = left_child;
    }
    if (right_child <= heap_size && heap[right_child] > heap[largest]) {
        largest = right_child;
    }
    if (largest != idx) {
        temp = heap[largest];
        heap[largest] = heap[idx];
        heap[idx] = temp;
        heapify(heap, largest, heap_size);
    }
}

void build_heap(int *heap, int heap_size) {
    for (int i = heap_size / 2; i > 0; i--) {
        heapify(heap, i, heap_size);
    }
}

int is_heap(int heap[], int idx, int size) {
    int left_child = idx * 2, right_child = idx * 2 + 1;

    if (left_child > size && right_child > size) return 1;

    if ((left_child <= size && heap[left_child] > heap[idx]) ||
        (right_child <= size && heap[right_child] > heap[idx])) {
        return 0;
    } else
        return is_heap(heap, left_child, size) && is_heap(heap, right_child, size);
}

int main(void) {
    Heap *heap = create_heap();
    int *input = (int *)malloc(sizeof(int) * (MAX_SIZE + 1));
    int *unordered = (int *)malloc(sizeof(int) * (MAX_SIZE + 1));

    srand(time(NULL));

    // random input generator
    printf("Generating random input...\n");
    for (int i = 1; i < MAX_SIZE + 1; i++) {
        input[i] = rand() % 100 + 1;
    }
    printf("Done!");

    // original input
    printf("\n\noriginal:\t");
    if (is_heap(input, 1, MAX_SIZE + 1))
        printf("This is a Heap!\n");
    else
        printf("This is NOT a Heap.\n");

    printf("O(n) heap:\t");
    // O(n) Build Heap
    for (int i = 1; i < MAX_SIZE + 1; i++) {
        unordered[i] = input[i];
    }
    build_heap(unordered, MAX_SIZE);

    // O(n) Build Heap result
    if (is_heap(unordered, 1, MAX_SIZE)) printf("This is a Heap!\n");

    printf("O(nlogn) heap:\t");
    // O(nlogn) Build Heap
    for (int i = 1; i < MAX_SIZE + 1; i++) {
        insert_max_heap(heap, input[i]);
    }

    // O(nlogn) Build Heap Result
    if (is_heap(heap->heap, 1, MAX_SIZE)) printf("This is a Heap!\n");

    //}
    free(heap);
    free(input);
    free(unordered);
    return 0;
}