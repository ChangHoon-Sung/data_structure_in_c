// BOJ 15828 Router
// Assign: ChangHoon Sung
//
// INPUT
// N: 라우터의 크기 (1 <= N <= 100,000)
/*
TRY #1 (부분 성공) - 스켈레톤 큐의 구현
내마음대로 큐를 만들려니까 이상하게 잘 안됐다.
신뢰할 수 있는 구조를 설계하는 것이 얼마나 중요한지 깨달았다.
또, 순환 큐에서 N개의 원소를 담기 위해 N + 1개의 공간이 필요하다는 것을 체감한다.

TRY #2 (정답) - 구조체 순환 큐의 구현
동적 할당시 free 잊지 말자.
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element data[100001];
    int rear;
    int front;
    int capacity;
} Queue;

void init_queue(Queue *q, int capacity) {
    q->front = q->rear = 0;
    q->capacity = capacity;
}

int is_full(Queue *q) {
    return ((q->rear + 1) % q->capacity == q->front);
}

int is_empty(Queue *q) {
    return (q->front == q->rear);
}

void enqueue(Queue *q, element e) {
    if (is_full(q)) {
        return;
    }
    q->rear = (++q->rear) % q->capacity;
    q->data[q->rear] = e;
}

element dequeue(Queue *q) {
    q->front = (q->front + 1) % q->capacity;
    return q->data[q->front];
}

void queue_print(Queue *q) {
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % q->capacity;
            printf("%d ", q->data[i]);

            if (i == q->rear) break;
        } while (i != q->front);
    } else {
        printf("empty");
    }
}

int main(void) {
    Queue buffer;
    int N, packet;

    scanf("%d", &N);
    init_queue(&buffer, N + 1);

    while (1) {
        scanf("%d", &packet);
        if (packet == -1) break;
        if (!packet)
            dequeue(&buffer);
        else
            enqueue(&buffer, packet);
    }

    queue_print(&buffer);
    return 0;
}