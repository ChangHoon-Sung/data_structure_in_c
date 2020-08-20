#include <stdio.h>
#define MAX(x, y) ((x) > (y)) ? x : y

typedef struct
{
    int L;
    int H;
} pole;

int main(void) {
    pole input[1000] = {};
    pole stack[1000] = {};
    pole tmp, hi = {-1, -1};
    int N, top = -1, ans = 0, hi_idx;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &input[i].L, &input[i].H);
    }

    // 최고 높이 폴 찾기
    for (int i = 0; i < N; i++) {
        if (input[i].H > hi.H) {
            hi = input[i];
        }
    }

    // 올라가기
    for (int i = 0; i < hi.L; i++) {
        tmp = input[i];
        while (top != -1 && stack[top].H < tmp.H) {
            top--;
        }
        stack[++top] = tmp;
    }
    hi_idx = top;

    // 오름 구간 넓이 구하기
    while (top > 0) {
        ans += (stack[top].L - stack[top - 1].L) * stack[top].H;
        top--;
    }

    // 최고 폴 넓이 구하기
    ans += hi.H;

    top = -1;
    // 내려가기
    for (int i = N - 1; i >= hi_idx; i--) {
        tmp = input[i];
        while (top != -1 && stack[top].H < tmp.H) {
            top--;
        }
        stack[++top] = tmp;
    }

    // 내림 구간 넓이 구하기
    while (top > 0) {
        ans += (stack[top].L - stack[top - 1].L) * stack[top].H;
        top--;
    }

    printf("%d", ans);

    return 0;
}