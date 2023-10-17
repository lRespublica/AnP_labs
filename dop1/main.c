#include <stdio.h>
#include <math.h>
#define mNAN 0.0/0.0

double mabs(double a)
{
    if(a < 0)
        return -a;
    else
        return a;
}

int mpow (int a, unsigned int n) {
    int res = 1;
    while(n)
    {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

double msqrt(double a)
{
    if(a < 0) return mNAN;
    const double acc = 1e-8;
    double x = 1;

    while(1)
    {
        double ax = (x + a/x)/2;
        if(mabs(ax - x) < acc)
            break;
        x = ax;
    }

    return x;
}

double mfreexp(double x)
{
    return mabs(x)-(int)(mabs(x));
}

double mlog(double a)
{
    if(a < 0) return mNAN;
    const double acc = 1e-8;
    double x = 0;

    while(1)
    {
        double ax = (x + 1/a)/2;
        if(mabs(ax - x) < acc)
            break;
        x = ax;
    }

    return x;
}

double mlogn(int a, int b)
{
    return mlog(a)/mlog(b);
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d %d %d %d %lf %lf %lf", a, b, mpow(a, b), (int)msqrt(a), mlog(a), mlog(b), mlogn(a, b));
}
