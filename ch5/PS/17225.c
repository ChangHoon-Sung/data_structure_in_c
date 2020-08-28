// BOJ 17225 세훈이의 선물가게
// Assign: ChangHoon Sung
//
// INPUT
// A, B, N: 파랑과 빨강 포장 속도(0 <= A, B <= 300), 손님 수(1 <= N <= 1,000)
// t, c, m: 주문 시각(1 <= t <= 86,400), 포장지 색(c == 'B' | 'R'), 선물의 갯수(1 <= m <= 100)

/*
TRY #1 (부분 성공) - 온 순서대로 바로바로 처리
여기까진 쉽다. 더 깔끔하게 짜보자.

TRY #2 (실패) - 우선순위 큐?
배우고 나서 재도전!
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 1000001

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef struct {
    int timestamp;
    int no;
} order;

typedef order element;

typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int rear;
    int front;
    int number_of_tasks;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = q->number_of_tasks = 0;
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
    q->rear = (q->rear + 1) % MAX_ELEMENT_SIZE;
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

Queue Red, Blue, RedOrderList, BlueOrderList;
int A, B, N;
int red_ans[MAX_ELEMENT_SIZE], blue_ans[MAX_ELEMENT_SIZE];
int R_i, B_i;

void get_order() {
    order order;
    int t, m;
    char c;
    for (int i = 0; i < N; i++) {
        scanf("%d %c %d", &t, &c, &m);
        order.no = -1;
        switch (c) {
            case 'B':
                for (int n = 0; n < m; n++) {
                    order.timestamp = t + n * A;
                    enqueue(&BlueOrderList, order);
                }
                break;
            case 'R':
                for (int n = 0; n < m; n++) {
                    order.timestamp = t + n * B;
                    enqueue(&RedOrderList, order);
                }
                break;
        }
    }
}

int isFinished() {
    return is_empty(&RedOrderList) && is_empty(&BlueOrderList);
}

int main(void) {
    int order_no = 1;
    int red_service_time, blue_service_time;

    init_queue(&Red);
    init_queue(&Blue);
    init_queue(&RedOrderList);
    init_queue(&BlueOrderList);

    scanf("%d %d %d", &A, &B, &N);
    blue_service_time = A - 1 > 0 ? A - 1 : 0;
    red_service_time = B - 1 > 0 ? B - 1 : 0;
    get_order();

    for (int t = 0; !isFinished(); t++) {
        order b;
        order r;

        if (!is_empty(&Blue)) {
            if (blue_service_time > 0)
                blue_service_time--;
            else {
                while (!is_empty(&Blue) && !blue_service_time) {
                    blue_service_time = A - 1 > 0 ? A - 1 : 0;
                    blue_ans[B_i++] = dequeue(&Blue).no;
                }
            }
        }

        if (!is_empty(&Red)) {
            if (red_service_time > 0)
                red_service_time--;
            else {
                while (!is_empty(&Red) && !red_service_time) {
                    red_service_time = B - 1 > 0 ? B - 1 : 0;
                    red_ans[R_i++] = dequeue(&Red).no;
                }
            }
        }

        while (!is_empty(&BlueOrderList) && peek(&BlueOrderList).timestamp <= t) {
            b = dequeue(&BlueOrderList);
            b.no = order_no++;
            Blue.number_of_tasks++;
            enqueue(&Blue, b);
        }

        while (!is_empty(&RedOrderList) && peek(&RedOrderList).timestamp <= t) {
            r = dequeue(&RedOrderList);
            r.no = order_no++;
            Red.number_of_tasks++;
            enqueue(&Red, r);
        }
    }

    while (!is_empty(&Blue)) {
        blue_ans[B_i++] = dequeue(&Blue).no;
    }
    while (!is_empty(&Red)) {
        red_ans[R_i++] = dequeue(&Red).no;
    }

    printf("%d\n", Blue.number_of_tasks);
    for (int i = 0; i < B_i; i++) {
        printf("%d ", blue_ans[i]);
    }
    printf("\n");

    printf("%d\n", Red.number_of_tasks);
    for (int i = 0; i < R_i; i++) {
        printf("%d ", red_ans[i]);
    }
    printf("\n");

    return 0;
}