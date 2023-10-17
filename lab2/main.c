#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

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
    
    if(x > 0)
    {
        if(y > 0)
        {
            if(2*x + y <= 1)
                printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
            else
                printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
        }
        else if(y <= 0)
        {
            if(2*x - y <= 1)
                printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
            else
                printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
        }
    }
    else if(x <= 0)
    {
        if(y > 0)
        {
            if(-2* x + y <= 1)
                printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
            else
                printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
        }
        else if(y <= 0)
        {
            if(-2*x - y <= 1)
                printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
            else
                printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
        }
    }

    if( ((x > 0) && (y > 0) && (2 * x + y <= 1)) || ((x > 0) && (y <= 0) && (2 * x - y <= 1))
            || ((x <= 0) && (y > 0) && (-2 * x + y <= 1)) || ((x <= 0) && (y <= 0) && (-2 * x - y <= 1)))
        printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
    else
        printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);

    if(isInArea(x, y))
        printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
    else
        printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);

    return 0;
}
