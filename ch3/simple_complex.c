#include <stdio.h>

typedef struct
{
    float real;
    float imaginary;
} Complex;

void print_complex(Complex a)
{
    printf("%3.1f + %3.1f * i\n", a.real, a.imaginary);
}

Complex complex_add(Complex a, Complex b)
{
    Complex c;
    c.real = a.real + b.real;
    c.imaginary = a.imaginary + b.imaginary;

    return c;
}

int main(void)
{
    Complex c1 = {3, 14}, c2 = {2, 18};
    print_complex(c1);
    print_complex(c2);
    print_complex(complex_add(c1, c2));
    return 0;
}