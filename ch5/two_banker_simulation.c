#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT_SIZE 100

void error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;
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

int main(void) {
    int number_of_banker = 2;
    int minutes = 10;
    int total_wait = 0;
    int total_customers = 0;
    int service_time[number_of_banker] = {};
    int service_customer[number_of_banker];
    Queue q;
    init_queue(&q);

    srand(time(NULL));
    for (int clock = 0; clock < minutes; clock++) {
        printf("현재시각=%d\n", clock);
        if ((rand() % 10) < 3) {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&q, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무처리시간= %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }
        for (int banker = 0; banker < 2; banker++) {
            if (service_time[banker] > 0) {
                printf("은행원 %d가 고객 %d 업무처리중입니다. \n", banker, service_customer[banker]);
                service_time[banker]--;
            } else {
                if (!is_empty(&q)) {
                    element customer = dequeue(&q);
                    for (int idle = 0; idle < 2; idle++) {
                        if (!service_time[idle]) {
                            service_customer[idle] = customer.id;
                            service_time[idle] = customer.service_time;
                            printf("은행원 %d가 %d분에 고객 %d의 업무를 시작합니다. 대기시간은 %d분이었습니다. \n", idle, clock, customer.id, clock - customer.arrival_time);
                            break;
                        }
                    }
                    total_wait += clock - customer.arrival_time;
                }
            }
        }
    }
    printf("전체 대기 시간=%d분 \n", total_wait);
    return 0;
}