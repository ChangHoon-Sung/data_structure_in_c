#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

// 스택 전역변수 선언
StackType brackets;

void init_stack(StackType *s) {
    s->top = -1;
}

int is_full(StackType *s) {
    return (s->top == MAX_ELEMENT_SIZE - 1);
}

int is_empty(StackType *s) {
    return (s->top == -1);
}

void push(StackType *s, element value) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 오류!");
        exit(1);
    } else {
        s->data[++(s->top)] = value;
    }
}

element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류!");
        exit(1);
    } else
        return s->data[(s->top)--];
}

int check_maching(const char *in) {
    StackType s;
    init_stack(&s);
    char ch, open_ch;

    for (int i = 0; i < strlen(in); i++) {
        ch = in[i];
        switch (ch) {
            case '(':
            case '{':
            case '[':
                push(&s, ch);
                break;

            case ')':
            case '}':
            case ']':
                if (is_empty(&s)) return 0;
                open_ch = pop(&s);
                if (open_ch == '(' && ch != ')' ||
                    open_ch == '{' && ch != '}' ||
                    open_ch == '[' && ch != ']') {
                    return 0;
                }
                break;
        }
    }

    if (!(is_empty(&s))) return 0;
    return 1;
}

int main(void) {
    char *p = "{ A[(i+1)]=0; }";

    if (check_maching(p)) {
        printf("%s success!", p);
    } else {
        printf("%s fail!", p);
    }

    return 0;
}
