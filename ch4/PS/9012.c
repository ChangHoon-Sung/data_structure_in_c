// BOJ 9012 괄호
// Assign: ChangHoon Sung
//
// INPUT
// T: 정수
// s: 2개 이상 50개 이하 '('와 ')'로 구성된 문자열

#include <stdio.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 50

typedef char element;
typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

// 스택 전역변수 선언
StackType brackets;

void init_stack(StackType *s) { s->top = -1; }  // 초기화되지 않은 data는 top이 움직이며 덮어씌우므로
                                                // top만 초기회해도 문제가 없다.

int is_full(StackType *s) { return (s->top == MAX_ELEMENT_SIZE - 1); }

int is_empty(StackType *s) { return (s->top == -1); }

void push(StackType *s, element value) {
    s->data[++(s->top)] = value;
}

element pop(StackType *s) {
    if (is_empty(s))
        return -1;
    else
        return s->data[(s->top)--];
}

int bracket_check(char s[]) {
    char b = 0, lb = 0;
    init_stack(&brackets);  // 스택 초기화.

    for (int i = 0; i < strlen(s); i++) {
        b = s[i];
        switch (b) {
            case '(':
                push(&brackets, b);
                break;

            case ')':
                lb = pop(&brackets);
                if (lb == -1 || lb == '(' && b != ')')
                    return 0;
                break;
        }
    }

    if (!is_empty(&brackets)) return 0;

    return 1;
}

int main(void) {
    int n;
    // 런타임 에러 원인! 포인터에 문자열주소를 직접 대입하지 말고, 메모리를 반드시 할당한 다음 문자열을 대입해라.
    // https://stackoverflow.com/questions/37549594/crash-or-segmentation-fault-when-data-is-copied-scanned-read-to-an-uninitializ
    // 다음과 같이도 가능하다. char * s = (char *)malloc(sizeof(char) * 50)
    char s[50];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        if (bracket_check(s))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
