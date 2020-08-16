#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 100

typedef char element;
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

int rank(char op) {
    switch (op) {
        case '*':
        case '/':
        case '%':
            return 2;

        case '+':
        case '-':
            return 1;

        case '(':
        case ')':
            return 0;
    }
    return -1;
}

void in2post(char *in, char *po) {
    int idx = 0;
    char ch, t;
    StackType op;
    init_stack(&op);

    for (int i = 0; i < strlen(in); i++) {
        ch = in[i];
        switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                // 체크중인 연산자보다 기존 연산자의 우선순위가 높으면
                // 그 연산자들이 먼저 계산되어야 하므로 다 바깥으로 빼준다.
                // 우선순위가 동등한 경우에도 순서에 따라 결과가 달라질 수 있으므로 빼준다.
                while (!is_empty(&op) && rank(ch) <= rank(peek(&op))) {
                    po[idx++] = pop(&op);
                }
                push(&op, ch);
                break;

            case '(':  // 왼괄호는 우선순위가 가장 낮으므로 무조건 들어간다.
                push(&op, ch);
                break;

            case ')':  // 왼괄호 전까지의 모든 연산자를 다 뺀다.
                t = pop(&op);
                while (t != '(') {
                    po[idx++] = t;
                    t = pop(&op);
                }
                break;
            default:  // 피연산자는 그냥 들어간다.
                po[idx++] = ch;
                break;
        }
    }
    while (!is_empty(&op)) {
        po[idx++] = pop(&op);
    }
}

int main(void) {
    char infix[100] = "a*(b+c)%d";
    char postfix[100] = {};

    printf("중위표시수식 %s\n", infix);
    in2post(infix, postfix);
    printf("후위표시수식 %s\n", postfix);
}