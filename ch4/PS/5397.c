// BOJ 5397 키로거
// Assign: ChangHoon Sung
//
// INPUT
// T: 테스트 케이스 정수 (주어지지 않음)
// N개의 L: 문자열  (1 <= L <= 1,000,000)

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 1000001

/* 스택 정의 시작 */
typedef char element;

typedef struct {
    element data[MAX_ELEMENT_SIZE];
    int top;
} StackType;

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

element peek(StackType *s) {
    if (is_empty(s))
        fprintf(stderr, "underflow");
    else
        return s->data[s->top];
}

char *stack_to_string(StackType *s) {
    return s->data;
}

/*
스택을 여러 개 사용할 수 있는 응용이 가능한지 보는 문제.
커서 좌, 커서 우에 해당하는 스택을 두면 쉽게 풀 수 있다.
'<' 연산에 대해 좌스택에서 우스택으로 요소 이동
'>' 연산에 대해 우스택에서 좌스택으로 요소 이동
'-' 연산에 대해서 좌스택 팝

각 스택이 비는지 잘 확인해준다.
문자열이 끝나면 모든 요소를 좌로 이동시켜 출력한다.
이때 문자열 마지막을 '\0'으로 장식하는 것을 잊지 말자.

'복잡한 자료형의 연산은 함수로 정의된다.'
stack_to_string 함수를 작성하면서 다시 한 번 이해한다.
*/

void solution() {
    char ch;
    StackType l, r;
    init_stack(&l);
    init_stack(&r);

    while ((ch = getchar()) != '\n') {
        switch (ch) {
            case '<':
                if (!is_empty(&l)) {
                    push(&r, pop(&l));
                }
                break;
            case '>':
                if (!is_empty(&r)) {
                    push(&l, pop(&r));
                }
                break;
            case '-':
                if (!is_empty(&l)) {
                    pop(&l);
                }
                break;
            default:
                push(&l, ch);
                break;
        }
    }

    while (!is_empty(&r)) {
        push(&l, pop(&r));
    }
    push(&l, '\0');

    printf("%s\n", stack_to_string(&l));

    return;
}

int main(void) {
    int N;
    scanf("%d", &N);
    getchar();

    for (int i = 0; i < N; i++)
        solution();
}