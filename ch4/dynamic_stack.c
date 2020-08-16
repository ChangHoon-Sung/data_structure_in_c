#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element *data;
    int top;
    int capacity;
} StackType;

void init_stack(StackType *s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(sizeof(element) * s->capacity);
    if (s->data == NULL) {
        fprintf(stderr, "malloc fail: no memory is available");
    }
}

int is_full(StackType *s) {
    return (s->top == s->capacity - 1);
}

int is_empty(StackType *s) {
    return (s->top == -1);
}

void push(StackType *s, element value) {
    // 스택 메모리 초과시 2배 추가 할당
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, sizeof(element) * s->capacity);
        if (s->data == NULL) {
            fprintf(stderr, "realloc fail: no memory is available");
        }
    }
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

int main(void) {
    StackType s;
    init_stack(&s);
    printf("%p\n", s.data);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    for (int i = 0; i < 3; i++) {
        printf("%d\n", pop(&s));
    }

    // 프로그램 종료 전, allocated된 모든 변수를 해제시켜야 한다.
    free(s.data);

    return 0;
}