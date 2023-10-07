#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isInArea(double x, double y)
{
    return fabs(y) + fabs(2*x) <= 1;
}

int main()
{
    double x, y;
    
    printf("Введите число x: ");
    scanf("%lf", &x);

    printf("Введите число y: ");
    scanf("%lf", &y);

    if(fabs(y) + fabs(2*x) <= 1)
        printf("Точка (%f, %f) принадлежит заданной области\n", x, y);
    else if(isInArea(x, y) == 0)
        printf("Точка (%f, %f) НЕ принадлежит заданной области\n", x, y);
}
