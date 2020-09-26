// LPT(Long Processing Time first) on Machine Scheduling
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct element {
    int id;
    int avail;
} element;

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

void insert_min_heap(Heap* h, element item) {
    int i = ++(h->heap_size);

    while (i != 1 && item.avail < h->heap[i / 2].avail) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

element delete_min_heap(Heap* h) {
    element item = h->heap[1];
    element temp = h->heap[(h->heap_size)--];

    int parent = 1, child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].avail > h->heap[child + 1].avail) {
            child++;
        }
        if (temp.avail < h->heap[child].avail) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

#define JOBS 7
#define MACHINES 3

int main(void) {
    int jobs[JOBS] = {8, 7, 6, 5, 3, 2, 1};
    element m = {0, 0};
    Heap* h = create_heap();
    init(h);

    for (int i = 0; i < MACHINES; i++) {
        m.id = i + 1;
        m.avail = 0;
        insert_min_heap(h, m);
    }

    for (int i = 0; i < JOBS; i++) {
        m = delete_min_heap(h);
        printf("JOB %d을 시간=%d부터 시간=%d까지 기계 %d번에 할당한다.\n", i, m.avail, m.avail + jobs[i] - 1, m.id);
        m.avail += jobs[i];
        insert_min_heap(h, m);
    }

    return 0;
}