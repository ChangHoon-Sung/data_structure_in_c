// BOJ 2504 괄호의 값
// Assign: ChangHoon Sung
//
// INPUT
// s: 괄호열  (1 <= s <= 30)
// s는 (, ), [, ]로만 구성된다.

#include <stdio.h>
#include <string.h>

#define MAX_ELEMENT_SIZE 35
int value[MAX_ELEMENT_SIZE]; // 괄호의 깊이에 따라 계산을 중간중간에 저장한다.

/* 스택 정의 시작 */
typedef char element; // 괄호만 다루므로 char로 제한한다.
typedef struct
{
    element data[MAX_ELEMENT_SIZE];
    int top;
} Stack;

void init_stack(Stack *s)
{
    s->top = -1;
}

int is_full(Stack *s)
{
    return (s->top == MAX_ELEMENT_SIZE - 1);
}

int is_empty(Stack *s)
{
    return (s->top == -1);
}

int push(Stack *s, element e)
{
    s->data[++(s->top)] = e;
}

element pop(Stack *s)
{
    return s->data[(s->top)--];
}
/* 스택 정의 끝 */

// 올바른 괄호열 검사
int is_correct(const char *in)
{
    Stack s;
    init_stack(&s);
    char ch, open_ch;

    for (int i = 0; i < strlen(in); i++)
    {
        ch = in[i];
        switch (ch)
        {
        case '(':
        case '[':
            push(&s, ch);
            break;

        case ')':
        case ']':
            // 닫는 괄호의 짝을 찾을 때 스택이 비어있는 경우
            if (is_empty(&s))
                return 0;

            open_ch = pop(&s);

            // 닫는 괄호의 올바른 짝이 아닌 경우
            if ((open_ch == '(' && ch != ')') ||
                (open_ch == '[' && ch != ']'))
            {
                return 0;
            }
            break;
        }
    }

    if (!(is_empty(&s)))
        return 0; // 모든 괄호를 조사했을 때 스택이 비어있지 않는 경우
    return 1;
}

// 아래 공식에 유의한다.
// 여는 괄호의 깊이 == 닫는 괄호의 깊이 - 1
void value_of_brackets(const char *brkts, int idx, int d)
{
    char ch;
    ch = brkts[idx];

    switch (ch)
    {
    case '(':
    case '[':
        value_of_brackets(brkts, idx + 1, d + 1); // 여는 괄호일 때 깊이 증가
        break;

    case ')':
        // 단독 괄호 ()인 경우 value[여는 괄호의 깊이]에 값 계산하여 저장
        if (brkts[idx - 1] == '(')
        {
            value[d - 1] += 2;
        }
        else
        {
            // 단독 괄호 ()가 아닌 경우 내부 계산 결과가 있다는 의미이다.
            // 공식을 응용하면 닫는 괄호의 깊이는 내부 계산 결과의 깊이와 같다.
            // 따라서 value[현재 깊이]에 곱셈 연산을 하여 value[여는 괄호의 깊이]에 더해준다.
            value[d - 1] += value[d] * 2;
            value[d] = 0;
        }
        if (0 < d)
        {
            // 닫는 괄호 처리가 끝나면 깊이를 감소시켜 다음 괄호열을 조사한다.
            // 이로 인해 공식이 자연스럽게 성립된다.
            value_of_brackets(brkts, idx + 1, d - 1);
        }
        break;

    // 위와 동일
    case ']':
        if (brkts[idx - 1] == '[')
        {
            value[d - 1] += 3;
        }
        else
        {
            value[d - 1] += value[d] * 3;
            value[d] = 0;
        }
        if (0 < d)
        {
            value_of_brackets(brkts, idx + 1, d - 1);
        }
        break;

    // 괄호 문자열 마지막에 '\0'을 만나면 조사가 끝난다.
    default:
        return;
    }
    return;
}

int main()
{
    int answer;
    char string[MAX_ELEMENT_SIZE] = {};
    scanf("%s", string);

    if (is_correct(string))
    {
        value_of_brackets(string, 0, 0);
        answer = value[0];
    }
    else
    {
        answer = 0;
    }
    printf("%d", answer);
}