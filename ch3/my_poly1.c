#include <stdio.h>

#define MAX(x, y) ((x) > (y)) ? (x) : (y)

#define MAX_DEGREE 101
typedef struct
{
    int degree;
    float coef[MAX_DEGREE];
} polynomial;

void print_poly(polynomial x)
{
    for (int i = 0; i < x.degree; i++)
    {
        if (x.coef[i] != 0)
            printf("%s%3.1fx^%d +", (x.coef[i] >= 0) ? " " : " -", x.coef[i], x.degree - i);
    }
    printf("%3.1f\n", x.coef[x.degree]);
}

polynomial add_poly(polynomial A, polynomial B)
{
    polynomial C;
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;
    C.degree = MAX(A.degree, B.degree);

    while (Apos <= A.degree && Bpos <= B.degree)
    {
        if (degree_a > degree_b)
        {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a < degree_b)
        {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
        else
        {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--, degree_b--;
        }
    }

    return C;
}

int main(void)
{
    polynomial a = {5, {10, 0, 0, 0, 6, 3}};
    polynomial b = {8, {3, 4, 0, 0, 0, 0, 0, 0}};
    print_poly(a);
    print_poly(b);
    print_poly(add_poly(a, b));
    return 0;
}
