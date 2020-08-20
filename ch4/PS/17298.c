// BOJ 17298 오큰수
// Assign: ChangHoon Sung
//
// INPUT
// S: 문자열  (1 <= S <= 1,000,000)
// B: 문자열  (1 <= B <= 36)
/*
TRY #1 (성공) - 스택과 정답 인덱스의 분리
핵심에 집중해서 간략하게 코드를 짜는 방법을 고민하는 중이다.
9935번 문자열 폭발의 답을 제시했던 고수는 어떻게 했을까? 하면서 말이다.

이번 문제는 정답의 인덱스 변수와 스택의 탑을 확실히 분리하면서 풀리기 시작했다.
수열 A의 새 원소가 들어올 때마다 현재 스택의 peek와 비교한다.
새 원소가 크면 팝하고 정답의 인덱스에 새 원소를 대입한다.
스택의 peek이 새 원소보다 클 때까지 반복한다.
스택이 비면 push한다.

모든 원소의 검사가 끝나면 정답배열이 비어있는 인덱스에 -1을 대입한다.
이는 그 원소에 해당하는 NGE가 없다는 뜻이다!

처음에 첫 원소와 마지막 원소에 대해서 따로 예외처리를 하려고 했지만,
답 실시간 출력 방식이 불가능하다는 것을 깨닫고 정답 배열에 담아 출력하기로 했다.

이번 문제를 성공적으로 풀어서 기쁘다!
채점 퍼센트가 얼마나 천천히 오르던지...
*/

#include <stdio.h>

#define MAX_ELEMENT_SIZE 1000000

typedef struct {
    int idx;
    int value;
} A;

A stack[MAX_ELEMENT_SIZE];
int ans[MAX_ELEMENT_SIZE];

int main(void) {
    int N, a, idx = 0, top = -1;
    A tmp;

    scanf("%d", &N);
    scanf("%d", &a);
    tmp.idx = 0, tmp.value = a;
    stack[++top] = tmp;

    for (int i = 1; i < N; i++) {
        scanf("%d", &a);

        while (top != -1 && stack[top].value < a) {
            ans[stack[top].idx] = a;
            top--;
        }

        tmp.idx = i, tmp.value = a;
        stack[++top] = tmp;
    }

    while (top != -1) {
        ans[stack[top--].idx] = -1;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
    }

    return 0;
}