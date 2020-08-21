// BOJ 2304 창고 다각형
// Assign: ChangHoon Sung
//
// INPUT
// N: 기둥 갯수  (1 <= N <= 1,000)
// N개의 L(위치)과 H(높이) (1 <= L, H <= 1,000)

/*
TRY #1, 2 (실패, 곧바로 성공) - 최고 폴 기준 스택 쌓기
시간복잡도: O(N)
처음에 입력이 순차적이지 않아서 헤맸으나 배열의 인덱스L에 H를 대입하는 것으로 정렬했다.
스택 문제라고 해서 스택을 어거지로 사용한 기분이다.
가장 큰 폴의 인덱스를 기준으로 왼쪽은 좌에서 우, 오른쪽은 우에서 좌로 배열을 조사한다.
이렇게 되면 스택 내부가 단조 증가하도록 할 수 있다.
좌측 넓이, 가장 큰 폴 단독 넓이, 우측 넓이로 나누어 계산하였다.

첫 제출 후 틀린 이유는 가장 높은 폴이 2개 이상인 경우 때문이다.
조사할 때 조건에 등호를 붙여 해결했다.

# 다른 관점 #
https://www.acmicpc.net/source/17130941
어떤 사람은 넓이를 구분구적법으로 풀었다.
1. 입력을 배열에 넣어 정렬하고 가장 큰 폴의 위치를 구분했다.
2. 가장 큰 폴의 위치를 HI, 크기 비교 변수를 tallest라고 하자.
3. 구간 [0, HI]을 순회한다.
3-1. tallest = max(tallest, input[i])
3-2. 그리고 tallest만큼 정답에 더한다(!)
4. 구간 [HI, 1001]을 '역방향으로' 순회한다.
4-1. tallest = max(tallest, input[i])
4-2. 그리고 tallest만큼 정답에 더한다(!)
5. 정답 출력

## 이 풀이의 포인트 ##
구간 [0, HI]에서는 현재 인덱스에서 창고의 높이는 현재까지 가장 높은 폴에 의해 결정된다.
구간을 순회하며 실시간으로 현재까지의 폴 중 가장 높은 것을 비교할 수 있고,
폴의 가로 길이는 1이므로 그저 현재까지의 폴 중 가장 높은 기둥의 길이를 정답에 더해주기만 하면 된다.
가장 높은 폴을 기준으로 우측으로는 단조 감소하므로 그저 역순으로 순회해주면 위와 같다.

깔끔하다!
스택에 담아 다시 이를 팝하며 계산하는 내 방식보다 효율적이다.
*/
#include <stdio.h>
#define MAX_ELEMENT_SIZE 1001

typedef struct
{
    int L;
    int H;
} pole;

int main(void) {
    int input[MAX_ELEMENT_SIZE] = {};
    pole stack[MAX_ELEMENT_SIZE] = {};
    pole tmp, hi = {-1, -1};
    int N, top = -1, ans = 0, hi_idx, temp;
    scanf("%d", &N);

    // 입력 및 최고 폴 찾기 O(N)
    for (int i = 0; i < N; i++) {
        scanf("%d", &temp);
        scanf("%d", &input[temp]);
        if (input[temp] > hi.H) {
            hi.H = input[temp];
            hi.L = temp;
        }
    }

    // 올라가기 O(N)
    for (int i = 0; i <= hi.L; i++) {
        if (!input[i]) continue;

        tmp.L = i, tmp.H = input[i];
        if (top == -1) {
            stack[++top] = tmp;
        } else if (stack[top].H <= tmp.H) {
            stack[++top] = tmp;
        }
    }

    // 오름 구간 넓이 구하기 O(N)
    while (top > 0) {
        ans += (stack[top].L - stack[top - 1].L) * stack[top - 1].H;
        top--;
    }

    // 최고 폴 넓이 구하기 O(1)
    ans += hi.H;

    top = -1;
    // 내려가기 O(N)
    for (int i = MAX_ELEMENT_SIZE - 1; i >= hi.L; i--) {
        if (!input[i]) continue;

        tmp.L = i, tmp.H = input[i];
        if (top == -1) {
            stack[++top] = tmp;
        } else if (stack[top].H <= tmp.H) {
            stack[++top] = tmp;
        }
    }

    // 오름 구간 넓이 구하기 O(N)
    while (top > 0) {
        ans += (stack[top - 1].L - stack[top].L) * stack[top - 1].H;
        top--;
    }

    printf("%d", ans);

    return 0;
}