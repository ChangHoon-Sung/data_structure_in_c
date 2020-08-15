#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int data;
    char string[20];
} Tag;

int main(void)
{
    Tag *t1;
    t1 = (Tag *)malloc(sizeof(Tag));

    t1->data = 100;

    // 문자열 주소에 담긴 문자는 상수이므로,
    // 배열에서 따옴표로 묶인 문자열을 이용하려면 꼭 strcpy를 통해 넣어주도록 하자.
    strcpy(t1->string, "just testing");

    free(t1);
    return 0;
}