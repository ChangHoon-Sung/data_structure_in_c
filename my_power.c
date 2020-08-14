#include <stdio.h>

// 빠른 제곱 계산
// 시간복잡도: O(logN)
double recursive_power(double x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n % 2 == 0)
    {
        return recursive_power(x * x, n / 2);
    }
    else
    {
        return x * recursive_power(x * x, (n - 1) / 2);
    }
}

int main()
{
    printf("%.lf", recursive_power(2, 64));
}