#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio_ext.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int main()
{
    int size;
    int x, y;
    double angel;
    int flag;

    printf("Введите размер квадрата: ");
    flag = scanf("%d", &size);
    CHECK_INPUT(flag);

    printf("Введите координаты квадрата: ");
    flag = scanf("%d", &x);
    CHECK_INPUT(flag);
    flag = scanf("%d", &y);
    CHECK_INPUT(flag);

    printf("Введите угол поворота: ");
    flag = scanf("%lf", &angel);
    CHECK_INPUT(flag);

    getchar();
    system("clear");

    for(int i = 0; i < y + size; i++)
    {
        if(i >= y)
        {
            for(int j = 0; j < x + size; j++)
            {
                if(j >= x)
                {
                    int fn1 = x;
                    int fn2 = x + size - 1;
                    int fn3 = y;
                    int fn4 = y + size - 1;
                    if(j == fn1 || j == fn2 || i == fn3 || i == fn4)
                        printf("*");
                    else
                        printf(" ");
                }
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    getchar();
    system("clear");

    angel = M_PI*angel/180;
    // ySize - высота. xSize - разность координат оснований
    int ySize = round(sin(angel) * size);
    int xSize = round(cos(angel) * size);
    for(int i = 0; i < y + ySize; i++)
    {
        if(i >= y)
        {
            for(int j = 0; j < x + xSize + size; j++)
            {
                int fn1 = y + round(tan(angel) * (j - size - x));
                int fn2 = y + round(tan(angel) * (j - x));
                int fn3 = y + ySize - 1;
                int fn4 = y;
                // Доп. условия для fn3 и fn4 предназначены для того, чтобы верхняя и нижния линии не выходили за границы
                if( i == fn1 || i == fn2 || (i == fn3 && j >= x + xSize) || (i == fn4 && j <= x + size && j >= x))
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
