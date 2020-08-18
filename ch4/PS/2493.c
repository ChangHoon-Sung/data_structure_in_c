// BOJ 2493 탑
// Assign: ChangHoon Sung
//
// INPUT
// N: 정수 (1 <= N <= 500,000)
// N개의 h: 탑의 높이  (1 <= h <= 100,000,000)

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT_SIZE 500001

/* 스택 정의 시작 */
typedef struct {
    int idx;
    int height;
} tower;

typedef struct {
    tower data[MAX_ELEMENT_SIZE];
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

void push(StackType *s, tower value) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 오류!");
        exit(1);
    } else {
        s->data[++(s->top)] = value;
    }
}

tower pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류!");
        exit(1);
    } else
        return s->data[(s->top)--];
}

tower peek(StackType *s) {
    if (is_empty(s))
        fprintf(stderr, "underflow");
    else
        return s->data[s->top];
}
/* 스택 정의 끝 */

/*
스택 연습용으로 풀어본 문제.
기본적인 아이디어는 스택 안에는 현재 탑보다 높거나 같은 탑의 정보만 필요하다는 것이다.

Try #1 (성공)
https://www.acmicpc.net/source/21823896
N이 1인 경우 바로 0을 출력하도록 예외처리.
현재 탑의 높이과 스택 가장 위의 탑의 높이를 비교.
현재 탑이 더 큰 동안 스택의 요소를 팝.
(이때 팝하다가 스택이 비는 경우를 체크하지 않아서 고생했다.)
스택이 비어있다면 0을 출력!
비어있지 않다면 peek해서 인덱스를 출력.
현재 탑을 스택에 넣음.
반복.

Try #2
성공하고나서 다른 코드를 봤더니 기똥찬 아이디어를 발견했다.
문제의 조건보다 항상 작거나 항상 큰 요소를 추가하는 테크닉.
0번 인덱스에 입력보다 항상 큰 탑을 넣는 것이다.
문제에서 인덱스를 1번부터 세기도 하니 아름답게 맞아 떨어진다.
스택에 항상 높은 탑을 넣고, 공백 스택에 대한 예외처리를 모두 걷어내었다.
이때 임의로 탑을 하나 추가한 것이므로 스택의 크기를 1만큼 크게 잡는다! (중요)
아래의 코드가 그것. 위보다 훨씬 깔끔하다.
*/

void solution(int N) {
    int h;
    tower tmp = {0, 100000001}, p;
    StackType s;
    init_stack(&s);
    push(&s, tmp);

    for (int i = 1; i < N; i++) {
        scanf("%d", &h);

        while (peek(&s).height < h) pop(&s);

        p = peek(&s);
        printf("%d ", p.idx);

        tmp.idx = i, tmp.height = h;
        push(&s, tmp);
    }
}

int main(void) {
    int N, tmp;
    scanf("%d", &N);
    solution(N + 1);
    return 0;
}