#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct element {
    int key;
    char* task;
} element;

typedef struct Heap {
    element heap[MAX_SIZE];
    int heap_size;
} Heap;

void insert_node(Heap* h, element e) {
    int i = ++h->heap_size;

    while (i != 1 && e.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}

element delete_node(Heap* h) {
    element item = h->heap[1];
    element temp = h->heap[h->heap_size--];

    int parent = 1, child = 2;
    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }
        if (temp.key > h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

char* get_string() {
    char* s = (char*)malloc(sizeof(char) * MAX_SIZE);
    scanf("%[^\n]s", s);
    printf("%s|\n", s);
    s[strlen(s) - 1] = 0;
    return s;
}

int main(void) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    element e;
    char ch;

    heap->heap_size = 0;
    while (1) {
        printf("삽입(i), 삭제(d), 종료(q): ");
        scanf("%c", &ch);
        while (getchar() != '\n') continue;  // 개행 제거

        switch (ch) {
            case 'i':
                printf("할일: ");
                e.task = get_string();

                printf("우선순위: ");
                scanf("%d", &e.key);
                getchar();  // 개행 제거

                insert_node(heap, e);
                break;

            case 'd':
                if (!heap->heap_size)
                    printf("힙이 비어있습니다.\n");
                else {
                    e = delete_node(heap);
                    printf("제일 우선 순위가 높은 일은 \"%s \"\n", e.task);
                    free(e.task);
                }
                break;

            case 'q':
                printf("종료합니다.");
                free(heap);
                exit(1);

            default:
                printf("알 수 없는 명령어\n");
        }
    }

    return 0;
}