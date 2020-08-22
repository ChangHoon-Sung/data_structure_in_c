#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 3

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef unsigned long long element;
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

int fibo(int n) {
    return (n == 1 || n == 0) ? n : fibo(n - 1) + fibo(n - 2);
}

int main(void) {
    int n;
    Queue q;
    init_queue(&q);
    enqueue(&q, 0);
    enqueue(&q, 1);

    printf("피보나치의 몇 번째 수열을 구할까요? > ");
    scanf("%d", &n);

    if (n == 0 || n == 1) {
        printf("피보나치 %d번째 수열은 %d 입니다.", n, n);
    } else {
        for (int i = 2; i <= n; i++) {
            enqueue(&q, dequeue(&q) + peek(&q));
        }
        dequeue(&q);
        printf("피보나치 %d번째 수열은 %lld 입니다.\n", n, dequeue(&q));
    }

    return 0;
}