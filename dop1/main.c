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

double mpowd (double a, unsigned int n) {
    double res = 1;
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

int mtrunc(double x)
{
    if(x > 0)
        return (int)x;
    else
        return (int)(x + mfreexp(x));
}

unsigned int mlog2(unsigned int a)
{
    unsigned int value = 0;
    while(a>1)
    {
        value++;
        a >>= 1;
    }
    return value;
}

double mlogn(unsigned int a, unsigned int b)
{
    return (double)mlog2(a)/(double)mlog2(b);
}

int main()
{
    int a, b, c;
    if (scanf("%d%d%d", &a, &b, &c) != 3)
    {
        printf("Invalid input\n");
        return 1;
    }
    double step1 = (double)a/b;
    double step2 = msqrt(step1);
    if(step2 != step2)
    {
        printf("Failed to calculate square root");
        return 1;
    }
    int step3 = mtrunc(step2);
    double step4 = mlogn(step3, c);
    if(step4 != step4)
    {
        printf("Failed to calculate log");
        return 1;
    }
    double step5 = mpowd(step4, b);
    double step6 = mround(step5);

    printf("%lf, %lf, %d, %lf, %lf, %lf", step1, step2, step3, step4, step5, step6);
}
