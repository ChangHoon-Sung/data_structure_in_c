// BOJ 13417 카드 문자열
// Assign: ChangHoon Sung
//
// INPUT
// T: 테스트 케이스 (1 <= T, T는 자연수)
// N: 카드 수 (1 <= N <= 1000)
// ch: 카드 알파벳 ('A' <= ch <= 'Z')

/*
Try #1 (정답) - 덱 활용하기
덱을 사용하는 문제임을 알 수 있는 말들.
'가져온 카드를 자신의 앞에 높인 카드들의 가장 왼쪽, 또는 가장 오른쪽에 놓는다.'
가장 앞과 가장 뒤에 추가/제거가 가능한 구조인 덱을 떠올릴 수 있다.
*/

#include <stdio.h>

#define MAX_ELEMENT_SIZE 1001

typedef char element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
} Deque;

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
    deq->rear = (deq->rear + 1) % MAX_ELEMENT_SIZE;
    deq->data[deq->rear] = e;
}

void add_front(Deque *deq, element e) {
    deq->data[deq->front] = e;
    deq->front = (deq->front - 1 + MAX_ELEMENT_SIZE) % MAX_ELEMENT_SIZE;
}

element get_front(Deque *deq) {
    if (is_empty(deq)) {
        return 'z' + 1;  // 첫 문자 예외처리
    }
    return deq->data[(deq->front + 1) % MAX_ELEMENT_SIZE];
}

void deque_print(Deque *q) {
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_ELEMENT_SIZE;
            printf("%c", q->data[i]);

            if (i == q->rear) break;
        } while (i != q->front);
    }
    printf("\n");
}

int main(void) {
    int T, N;
    char ch;
    Deque deq;

    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        init_deque(&deq);

        scanf("%d", &N);
        getchar();

        while ((ch = getchar()) != '\n') {
            if (ch == ' ') continue;

            if (ch <= get_front(&deq))
                add_front(&deq, ch);
            else
                add_rear(&deq, ch);
        }

        deque_print(&deq);
    }

    return 0;
}