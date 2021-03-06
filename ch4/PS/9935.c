// BOJ 9935 문자열 폭발
// Assign: ChangHoon Sung
//
// INPUT
// S: 문자열  (1 <= S <= 1,000,000)
// B: 문자열  (1 <= B <= 36)

/*
TRY #1 - 문자열을 스택으로 다루기
스택에 문자를 넣다가 폭발 문자열의 마지막 문자를 만나면
마지막 문자를 임시 스택에 넣고, 원래 스택의 문자를 폭발 문자열의 크기만큼 pop하며 일치 검사 (pop하면서 일치 검사하는 것도 문제다.)
(이 아래도 문제점다.)
일치하면 그대로 임시스택 버리기 
중간에 일치하지 않으면 도로 스택에 넣어주기.

TRY #2 - 폭발 스타트 트리거 인덱스를 스택에 넣기.
이거인듯.
문자열을 한 글자씩 받으면서 폭발물 스타트 인덱스를 스택에 넣는다.
폭발물 문자열을 받는다.
인덱스 스택에서 하나를 꺼내어 검사, 인덱스 - 1 위치와 폭발물 마지막 글자 + 1 문자열끼리 이어붙이기?
일단 시도
결론적으로 실패

## 도저히 모르겠다 ##

TRY #3 (답안) - #1을 좀 더 빠르게 할 수 있었다.
자료구조는 문제를 효율적으로 풀기 위해 존재하는 형태일 뿐이다.
여기에 너무 얽매이지 말자. 이건 문제풀이지, 팀 프로젝트가 아니니까.

마지막 문자를 만나면 마지막 문자로부터 거꾸로 조사해서
폭발 문자열과 일치하면 그 문자열을 날려버린다는 컨셉은 일치하다.
다만 시간을 줄이지 못한 부분은 임시 스택의 존재와 쓸데없는 push & pop 연산.

내가 자료구조에 얽매여 보지 못한 것은..
스택은 배열로 만들었으니 인덱스 접근이 가능하는 점.
내가 지금까지 스택 초기화를 top = -1로 해온 것처럼,
일부 문자열만큼만 삭제하기 위해 top을 임의로 조절 할 수 있었다는 점이다.

다음은 어떤 고수의 코드를 내가 쓰던 변수로 카피코딩한 것이다.
시간은 쓸데없이 오래 걸렸고, 중간 중간 때려치고싶었지만 끝까지 잘 버텼다.
오늘도 또 하나 배웠다.

코드 출처
https://kesakiyo.tistory.com/4
*/
#include <stdio.h>
#include <string.h>

int box_len, b_len, idx;
char box[1000001], bomb[37], ans[1000001];

int is_bomb(int s) {
    for (int i = s; i < s + b_len; i++) {
        if (ans[i] != bomb[i - s]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    scanf("%s", box);
    scanf("%s", bomb);
    box_len = strlen(box);
    b_len = strlen(bomb);

    for (int i = 0; i < box_len; i++) {
        ans[idx++] = box[i];
        if (idx - b_len >= 0 && is_bomb(idx - b_len)) {
            idx -= b_len;
        }
    }
    ans[idx] = '\0';
    printf("%s", idx ? ans : "FRULA");

    return 0;
}