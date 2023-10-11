#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CHECK_INPUT(flag) if (!flag) {printf("Incorrect input\n"); return 1;};

int isInArea(double x, double y)
{
    return fabs(y) + fabs(2*x) <= 1;
}

int main()
{
    double x, y;
    int flag;

    printf("Введите число x: ");
    flag = scanf("%lf", &x);

    CHECK_INPUT(flag);

    printf("Введите число y: ");
    flag = scanf("%lf", &y);

    CHECK_INPUT(flag);
    
    if(fabs(y) + fabs(2*x) <= 1)
        printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
    else if(isInArea(x, y) == 0)
        printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
}
