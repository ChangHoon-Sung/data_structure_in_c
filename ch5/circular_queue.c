#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 11

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = 0;
}

int is_full(Queue *q) {
    return ((q->rear + 1) % MAX_ELEMENT_SIZE == q->front);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, element e) {
    if (is_full(q)) {
        error("큐 포화 에러");
    }
    q->rear = (++q->rear) % MAX_ELEMENT_SIZE;
    q->data[q->rear] = e;
}

element dequeue(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    q->front = (q->front + 1) % MAX_ELEMENT_SIZE;
    return q->data[q->front];
}

element peek(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[(q->front + 1) % MAX_ELEMENT_SIZE];
}

void queue_print(Queue *q) {
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_ELEMENT_SIZE;
            printf("%d | ", q->data[i]);

            if (i == q->rear) break;
        } while (i != q->front);
    }
    printf("\n");
}

int main(void) {
    Queue q;
    init_queue(&q);

    for (int i = 0; i < 10; i++) {
        enqueue(&q, i);
        queue_print(&q);
    }

    for (int i = 0; i < 10; i++) {
        dequeue(&q);
        queue_print(&q);
    }

    return 0;
}