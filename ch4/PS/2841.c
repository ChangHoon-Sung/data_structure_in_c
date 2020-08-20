// BOJ 2841 외계인의 기타 연주
// Assign: ChangHoon Sung
//
// INPUT
// 음의 수: N  (N <= 500,000)
// 프렛의 수: P  (2 <= P <= 300,000)
/*
TRY #1 (성공) - 문제를 잘 읽자
하마터면 음의 수만큼 프렛을 만들 뻔했다.
문제 푸는데 600GB가 드는건 말이 안됐다.
만약 크기가 작게 나왔으면 오랫동안 삽질했을 것이다.

줄은 6개다.
각 줄에 해당하는 스택에 30만개의 프렛을 담을 공간을 할당한다.
그리고 각 줄에 대하여 조건에 따라 top을 조절해주면서 그 횟수를 세면 된다.

마지막에 오차가 발생한 이유는
같은 줄 같은 음 같은 프렛이 들어오는 경우 때문이다.
이 경우에는 스택에 넣지도 않고, 횟수도 증가시키지 않는다.
그 상태에서 튕기기만 하면 되기 때문이다.
*/
#include <stdio.h>

int main(void) {
    int stack[6][300000] = {};
    int top[6] = {-1, -1, -1, -1, -1, -1};
    int N, F, n, f, ans = 0;
    scanf("%d %d", &N, &F);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &n, &f);
        n--;

        while (top[n] != -1 && stack[n][top[n]] > f) {
            top[n]--;
            ans++;
        }

        if (stack[n][top[n]] != f) {
            stack[n][++top[n]] = f;
            ans++;
        }
    }

    printf("%d", ans);

    return 0;
}