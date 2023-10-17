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

int mpowd (double a, unsigned int n) {
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

int mround(double x)
{
    if(x >= 0)
        return mfreexp(x) >= 0.5 ? (int)x + 1 : (int)x;
    else
        return mfreexp(x) >= 0.5 ? (int)x - 1 : (int)x;
}

unsigned int mlog2(unsigned int a)
{
    unsigned int value = 0;
    while(a)
    {
        value++;
        a >>= 1;
    }
    return value;
}

double mlogn(int a, int b)
{
    return (double)mlog2(a)/mlog2(b);
}

int main()
{
    int a, b, c;
    scanf("%d%d", &a, &b, &c);
    int res = (int)(mpowd(mlogn((int)(msqrt((double)a/b)), c), b));
    printf("%d, %d, %d, %d", mround(1.23), mround(1.6), mround(-1.23), mround(-1.6));
}
