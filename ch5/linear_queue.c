#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 100

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
    q->front = -1;
    q->rear = -1;
}

int is_full(Queue *q) {
    return (q->rear == MAX_ELEMENT_SIZE - 1);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, element e) {
    if (is_full(q)) {
        error("큐 포화 에러");
    }
    q->data[++(q->rear)] = e;  // 스택과 유사하다.
}

element dequeue(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[++(q->front)];  // front도 -1에서 출발하므로 전위 증가
}

element peek(Queue *q) {
    if (is_empty(q)) {
        error("큐 공백 에러");
    }
    return q->data[(q->front)];
}

int main(void) {
    Queue q;
    init_queue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    for (int i = 0; i < 3; i++) {
        printf("%d ", dequeue(&q));
    }

    return 0;
}