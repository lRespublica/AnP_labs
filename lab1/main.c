#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int x, y;
    double z;

    printf("Введите число x: ");
    scanf("%d", &x);

    printf("Введите число y: ");
    scanf("%d", &y);

    printf("Введите число z: ");
    scanf("%lf", &z);

    printf("\n%-10d\n%-10d\n%-10.5e\n\n", x, y, z);
    
    double a = cbrt(abs(x-y)) * log(0.5 + fabs(((x+pow(y,2))/9))) / (pow(z,2) + 3*z +5);
    double b = exp(-x+z) * atan(z/3) / (pow(x,2) - 6*y +12);

    printf("a = %.4f\nb = %.4f\nx = %o\ny = %x\n", a, b, x, y);
}
