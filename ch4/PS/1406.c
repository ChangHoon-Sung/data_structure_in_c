// BOJ 1406 에디터
// Assign: ChangHoon Sung
//
// INPUT
// init_string: 초기 입력값 (1 <= N <= 100,000)
// N: 명령어의 갯수  (1 <= N <= 500,000)
// N개의 op 또는 arg: 'L', 'D', 'B', "P $"로 이루어진 명령어

/*
TRY #1 (성공) - 커서 스택 문제
저번에 성공했던 2개의 스택 사용
필요한 연산만 함수로 정의
스택의 배열 구조 적극 활용(문자열 출력과 top 위치 조정 등)

결과는 성공적.
C언어 랭크 22위! 나름 빠른 속도, 적당한 메모리 사용
*/

#include <stdio.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 600001

typedef struct {
    char data[MAX_ELEMENT_SIZE];
    int top;
} Stack;

Stack left, right;

void init_stack(Stack *s) {
    s->top = -1;
}

int is_full(Stack *s) {
    return (s->top == MAX_ELEMENT_SIZE - 1);
}
int is_empty(Stack *s) {
    return (s->top == -1);
}
void push(Stack *s, char c) {
    s->data[++s->top] = c;
}
char pop(Stack *s) {
    return s->data[s->top--];
}
char peek(Stack *s) {
    return s->data[s->top];
}

int main(void) {
    int N;
    char op, arg;
    init_stack(&left);
    init_stack(&right);

    scanf("%s", left.data);
    left.top = strlen(left.data) - 1;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        getchar();
        op = getchar();
        switch (op) {
            case 'L':
                if (!is_empty(&left)) {
                    push(&right, pop(&left));
                }
                break;
            case 'D':
                if (!is_empty(&right)) {
                    push(&left, pop(&right));
                }
                break;
            case 'B':
                if (!is_empty(&left)) {
                    left.top--;
                }
                break;
            case 'P':
                scanf(" %c", &arg);
                push(&left, arg);
                break;
        }
    }

    push(&left, '\0');
    printf("%s", left.data);
    while (right.top != -1) {
        printf("%c", right.data[right.top--]);
    }
}