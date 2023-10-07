#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fact(int num)
{
    int value = 1;
    while(num > 0)
    {
        value *= num;
        num--;
    }

    return value;
}

double atanStep(double x, int i)
{
    return pow(-1, i - 1) * pow(x, 2*i - 1) / fact(2*i - 1);
}

double calcWithAccuracy(const double x, const int n)
{
    double value = 0.0;
    double pastValue = 0.0;

    int i = 1;
    double avaitDiff = pow(0.1, n);
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

double calcBySteps(const double x, const double n)
{
    double value = 0.0;
    
    for (int i = 1; i <= n; i++)
        value += atanStep(x, i);

    return value;
}

int main()
{
    double x;
    unsigned int n, type;

    printf("Введите число x: ");
    scanf("%lf", &x);

    if (fabs(x) > 1)
    {
        printf("Ошибка: Число x ∉ [-1, 1]\n");
        return 1;
    }

    printf("\nВыберите способ посчёта:\n");
    printf(" 1. С заданной точностью\n");
    printf(" 2. Для заданного количества членов ряда\n");
    printf("> ");
    scanf("%u", &type);
    
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
