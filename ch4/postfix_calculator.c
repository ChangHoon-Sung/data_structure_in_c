#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 100

typedef double element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

void init_stack(StackType *s) { s->top = -1; }

int is_full(StackType *s) { return (s->top == MAX_ELEMENT_SIZE - 1); }

int is_empty(StackType *s) { return (s->top == -1); }

void push(StackType *s, element value) {
    if (is_full(s)) {
        fprintf(stderr, "overflow");
        exit(1);
    } else
        s->data[++(s->top)] = value;
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "underflow");
        exit(1);
    } else
        return s->data[(s->top)--];
}

element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "underflow");
        exit(1);
    } else
        return s->data[s->top];
}

double postfix_calculator(char *in) {
    char ch;
    StackType s;
    init_stack(&s);

    for (int i = 0; i < strlen(in); i++) {
        ch = in[i];
        if (48 <= ch && ch <= 57) {
            push(&s, (double)(ch - 48));
        } else {
            double b = pop(&s);
            double a = pop(&s);

            switch (ch) {
                case '+':
                    push(&s, a + b);
                    break;
                case '-':
                    push(&s, a - b);
                    break;
                case '*':
                    push(&s, a * b);
                    break;
                case '/':
                    push(&s, a / b);
                    break;
            }
        }
    }

    return pop(&s);
}

int main(void) {
    char exp[100];
    scanf("%s", exp);

    printf("%s = %.2lf", exp, postfix_calculator(exp));
    return 0;
}