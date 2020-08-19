// BOJ 1406 에디터
// Assign: ChangHoon Sung
//
// INPUT
// init_string: 초기 입력값 (1 <= N <= 100,000)
// N: 명령어의 갯수  (1 <= N <= 500,000)
// N개의 op 또는 arg: 'L', 'D', 'B', "P $"로 이루어진 명령어

/*
TRY #1 (실패) - 문자열 폭발의 쉬운 버전
말 그대로 쉬운 버전이다.
입력을 받은 뒤, 스택으로 한 번 더 체크하는 방식을 채택했다.
결과는 시간초과.

TRY #2 (정답) - 실시간 처리
폭발 문자열과는 다르게, 이 경우에는 매칭 조건이 단순하고 분명하기 때문에
실시간으로 받으면서 해결해도 문제가 없다.

결과는 성공적.
C언어 랭크 2위! 평균 빠른 속도, 적은 메모리 사용.
코드 길이를 줄이면 1위도 할 수 있지만, 그럼 지저분하니까.

BOJ 기준, 전역 변수보다 로컬 선언이 더 메모리를 적게 먹는다.
*/
#include <stdio.h>

int main(void) {
    char stack[100001];
    int N, top = -1;
    int cnt = 0;
    char ch;

    scanf("%d", &N);
    getchar();

    for (int i = 0; i < N; i++) {
        top = -1;
        while ((ch = getchar()) != '\n') {
            stack[++top] = ch;
            if (stack[top - 1] == stack[top] && top > 0) top -= 2;
        }
        if (top == -1) cnt++;
    }

    printf("%d", cnt);
    return 0;
}