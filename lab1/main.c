#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int main()
{
    int x, y;
    double z;
    int flag;

    printf("Введите число x: ");
    flag = scanf("%d", &x);
    CHECK_INPUT(flag);

    printf("Введите число y: ");
    flag = scanf("%d", &y);
    CHECK_INPUT(flag);

    printf("Введите число z: ");
    flag = scanf("%lf", &z);
    CHECK_INPUT(flag);

    printf("\n%-10d\n%-10d\n%-10.5e\n\n", x, y, z);
    
    double a = cbrt(abs(x-y)) * log(0.5 + fabs(((x+pow(y,2))/9))) / (pow(z,2) + 3*z +5);
    double b = exp(-x+z) * atan(z/3) / (pow(x,2) - 6*y +12);

    printf("a = %.4f\nb = %.4f\nx = %o\ny = %x\n", a, b, x, y);

    return 0;
}
