// BOJ 1935 후위 표기식 2
// Assign: ChangHoon Sung
//
// INPUT
// N: 정수 (1 <= N <= 26)
// s: 후위 표기식  (s <= 100)
// N개의 X: 알파벳에 대응되는 정수

#include <stdio.h>
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
    s->data[++(s->top)] = value;
}

element pop(StackType *s) {
    return s->data[(s->top)--];
}

double postfix_calculator(const int *num, char *in) {
    char ch;
    StackType s;
    init_stack(&s);

    for (int i = 0; i < strlen(in); i++) {
        ch = in[i];
        if ('A' <= ch && ch <= 'Z') {
            push(&s, (double)num[ch - 65]);  // 알파벳에 대응되는 수가 char을 벗어날 수 있는 정수임을 깜빡해서 틀렸다.
                                             // 토큰을 읽을 때 이에 대응하는 수를 스택에 직접 넣는 방법으로 해결!
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
    int N;
    int num[26] = {};
    char s[100] = {};

    scanf("%d", &N);
    scanf("%s", s);
    for (int i = 0; i < N; i++) {
        scanf("%d", &num[i]);
    }

    printf("%.2lf", postfix_calculator(num, s));

    return 0;
}