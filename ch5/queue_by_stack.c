#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 5

typedef int element;

typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

typedef struct {
    StackType in, out;
} Queue;

/* 스택 정의 시작 */
void init_stack(StackType *s) { s->top = -1; }

int is_full(StackType *s) { return (s->top == MAX_ELEMENT_SIZE - 1); }

int is_empty(StackType *s) { return (s->top == -1); }

void push(StackType *s, element value) {
    if (is_full(s))
        fprintf(stderr, "overflow");
    else
        s->data[++(s->top)] = value;
}

element pop(StackType *s) {
    if (is_empty(s))
        fprintf(stderr, "underflow");
    else
        return s->data[(s->top)--];
}

element peek(StackType *s) {
    if (is_empty(s))
        fprintf(stderr, "underflow");
    else
        return s->data[s->top];
}
/* 스택 정의 끝 */

/* 큐 정의 시작 */
void init_queue(Queue *q) {
    q->in.top = -1;
    q->out.top = -1;

    // 원래는 해줄 필요가 없으나 예쁜 출력을 위해서 추가한다.
    memset(q->in.data, 0, sizeof(q->in.data));
    memset(q->out.data, 0, sizeof(q->out.data));
}

int q_is_full(Queue *q) {
    return (is_full(&q->in) && is_full(&q->out));
}

int q_is_empty(Queue *q) {
    return (is_empty(&q->in) && is_empty(&q->out));
}

void enqueue(Queue *q, element e) {
    if (q_is_full(q)) {
        fprintf(stderr, "큐 포화 오류");
        exit(1);
    }
    if (is_full(&q->in)) {
        while (!is_empty(&q->in)) push(&q->out, pop(&q->in));
    }
    push(&q->in, e);
}
element dequeue(Queue *q) {
    if (q_is_empty(q)) {
        fprintf(stderr, "큐 공백 오류");
        exit(1);
    }
    if (is_empty(&q->out)) {
        while (!is_empty(&q->in)) push(&q->out, pop(&q->in));
    }
    pop(&q->out);
}

void queue_print(Queue *q) {
    printf("-----------------------------------------------------------\n");
    printf("Front Stack\t\t\tBack Stack\n");
    for (int i = 0; i < MAX_ELEMENT_SIZE; i++) {
        printf("%d | ", q->in.data[i]);
    }
    printf("\t\t");
    for (int i = 0; i < MAX_ELEMENT_SIZE; i++) {
        printf("%d | ", q->out.data[i]);
    }
    printf("\n\n");
}
/* 큐 정의 끝 */

int main(void) {
    int dequed;
    int output[MAX_ELEMENT_SIZE * 2] = {};
    Queue q;
    init_queue(&q);

    for (int i = 1; i <= 10; i++) {
        enqueue(&q, i);
        queue_print(&q);
    }

    for (int i = 0; i < 20; i++) {
        output[i] = dequeue(&q);

        queue_print(&q);

        printf("Output: ");
        for (int i = 0; i < 10; i++) {
            if (output[i]) printf("%d ", output[i]);
        }
        printf("\n-----------------------------------------------------------\n");
        printf("\n\n");
    }

    return 0;
}