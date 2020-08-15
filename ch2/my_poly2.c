#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct
{
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS] = {{8, 3}, {7, 1}, {1, 0}, {10, 3}, {3, 2}, {1, 0}};
int avail = 6; // 사용 가능한 공간의 첫 번째 인덱스

// 두 정수 비교
char compare(int a, int b)
{
    if (a > b)
        return '>';
    else if (a < b)
        return '<';
    else
        return '=';
}

// 공유 공간에 새로운 다항식 추가하기
void attach(float coef, int expon)
{
    // 공유 공간 초과시
    if (avail > MAX_TERMS)
    {
        fprintf(stderr, "항의 갯수가 너무 많음!\n");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

// 공유 공간에 담은 두 다항식 더하기
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
    float tempcoef;
    *Cs = avail;

    while (As <= Ae && Bs <= Be)
    {
        switch (compare(terms[As].expon, terms[Bs].expon))
        {
        case '>':
            attach(terms[As].coef, terms[As].expon);
            As++;
            break;
        case '<':
            attach(terms[Bs].coef, terms[Bs].expon);
            Bs++;
            break;
        case '=':
            tempcoef = terms[As].coef + terms[Bs].coef;
            if (tempcoef)
            {
                attach(terms[As].coef + terms[Bs].coef, terms[As].expon);
                As++, Bs++;
            }
            break;
        }
    }

    // A와 B 중 아직 더해지지 않은 다항식의 나머지 부분 붙이기
    for (; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);

    for (; Bs <= Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);

    // 새 다항식의 마지막 인덱스 저장
    *Ce = avail - 1;
}

void print_poly(int s, int e)
{
    for (int i = s; i < e; i++)
    {
        printf("%3.1fx^%d +", terms[i].coef, terms[i].expon);
    }
    printf("%3.1f\n", terms[e].coef);
}

int main(void)
{
    int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce;
    poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly(As, Ae);
    print_poly(Bs, Be);
    printf("--------------------------------------\n");
    print_poly(Cs, Ce);
    return 0;
}