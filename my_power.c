#include <stdio.h>
#include <time.h>

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

double iterative_power(double x, int n)
{
    double result = 1;
    if (n == 0)
        return result;
    else
    {
        for (int i = 1; i <= n; i++)
            result *= x;
    }
    return result;
}

int main()
{
    printf("Calculate 2^500, repeat 1 million times.\n");

    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
        recursive_power(2, 500);
    clock_t end = clock();
    printf("recursive power takes %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < 1000000; i++)
        iterative_power(2, 500);
    end = clock();
    printf("iterative power takes %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}