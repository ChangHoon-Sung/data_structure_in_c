#include <stdio.h>

#define MAX_ELEMENT_SIZE 11
#define MAX(X, Y) (((X) > (Y)) ? X : Y)

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} Stack;

Stack l, r;

void init_stack(Stack *s) { s->top = -1; }

int is_full(Stack *s) { return (s->top == MAX_ELEMENT_SIZE - 1); }

int is_empty(Stack *s) { return (s->top == -1); }

void push(Stack *s, element value) {
    s->data[++(s->top)] = value;
}

element pop(Stack *s) {
    return s->data[(s->top)--];
}
element peek(Stack *s) { return s->data[s->top]; }

int main(void) {
    int ans[MAX_ELEMENT_SIZE] = {};
    int N, a, max_value = 0;
    init_stack(&l);
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a);

        while (!is_empty(&l) && peek(&l) <= a) {
            ans[l.top + 1] = pop(&l);
            printf("%d ", a);
        }

        push(&l, a);
    }
    printf("-1");

    return 0;
}