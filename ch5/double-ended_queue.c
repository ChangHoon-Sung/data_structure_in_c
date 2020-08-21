#include <stdio.h>

#define MAX_ELEMENT_SIZE 10

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Deque;

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
}

void init_deque(Deque *deq) {
    deq->rear = 0;
    deq->front = 0;
}

int is_full(Deque *deq) {
    return ((deq->rear + 1) % MAX_ELEMENT_SIZE == deq->front);
}

int is_empty(Deque *deq) {
    return (deq->front == deq->rear);
}

void add_rear(Deque *deq, element e) {
    if (is_full(deq)) {
        error("덱 포화 에러");
    }
    deq->rear = (deq->rear + 1) % MAX_ELEMENT_SIZE;
    deq->data[deq->rear] = e;
}

void add_front(Deque *deq, element e) {
    if (is_full(deq)) {
        error("덱 포화 에러");
    }
    deq->data[deq->front] = e;
    deq->front = (deq->front - 1 + MAX_ELEMENT_SIZE) % MAX_ELEMENT_SIZE;
}

element delete_rear(Deque *deq) {
    int prev = deq->rear;
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    deq->rear = (deq->rear - 1 + MAX_ELEMENT_SIZE) % MAX_ELEMENT_SIZE;
    return deq->data[prev];
}

element delete_front(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    deq->front = (deq->front + 1) % MAX_ELEMENT_SIZE;
    return deq->data[deq->front];
}

element get_rear(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    return deq->data[deq->rear];
}

element get_front(Deque *deq) {
    if (is_empty(deq)) {
        error("덱 공백 에러");
    }
    return deq->data[(deq->front + 1) % MAX_ELEMENT_SIZE];
}

void deque_print(Deque *q) {
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
    Deque deq;
    init_deque(&deq);

    for (int i = 0; i < 3; i++) {
        add_front(&deq, i);
        deque_print(&deq);
    }
    for (int i = 0; i < 3; i++) {
        delete_rear(&deq);
        deque_print(&deq);
    }

    return 0;
}