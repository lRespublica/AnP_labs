#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

unsigned int fact(unsigned int num)
{
    unsigned int value = 1;
    while(num > 0)
    {
        value *= num;
        num--;
    }

    return value;
}

double atanStep(const double x, const int i)
{
    return pow(-1, i - 1) * pow(x, 2*i - 1) / (2*i - 1);
}

double calcWithAccuracy(const double x, const unsigned int n)
{
    double value = 0.0;
    double pastValue = 0.0;

    unsigned int i = 1;
    const double avaitDiff = pow(0.1, n);
    double currDiff;

    do 
    {
        pastValue = value;
        value += atanStep(x, i);
        i++;

        currDiff = fabs(pastValue - value);
    } while(currDiff > avaitDiff);

    return value;
}

double calcBySteps(const double x, const unsigned int n)
{
    double value = 0.0;
    
    for (int i = 1; i <= n; i++)
        value += atanStep(x, i);

    return value;
}

int main()
{
    double x;
    int flag;
    unsigned int n, type;

    printf("Введите число x: ");
    flag = scanf("%lf", &x);
    CHECK_INPUT(flag);

    if (fabs(x) >= 1)
    {
        printf("Ошибка: Число x ∉ [-1, 1]\n");
        return 1;
    }

    printf("\nВыберите способ посчёта:\n");
    printf(" 1. С заданной точностью\n");
    printf(" 2. Для заданного количества членов ряда\n");
    printf("> ");
    flag = scanf("%u", &type);
    CHECK_INPUT(flag);
    
    switch(type)
    {
        case 1:
            printf("\nВведите точность:\n> ");
            scanf("%u", &n);
            
            printf("Значение arctg(%f) со степенью точности %u = %f\n", x, n, calcWithAccuracy(x, n));

            break;

        case 2:
            printf("\nВведите количество шагов:\n> ");
            scanf("%u", &n);

            printf("Значение arctg(%f) за %u шагов вычислений = %f\n", x, n, calcBySteps(x, n));

            break;

        default:
            printf("Неизвестная опция\n");
            
            return 1;

            break;
    }

    return 0;
}
