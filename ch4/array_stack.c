#include <stdio.h>

#define MAX_ELEMENT_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

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

int main(void) {
    StackType s;
    init_stack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    for (int i = 0; i < 3; i++) {
        printf("%d\n", pop(&s));
    }

    return 0;
}