#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <unistd.h>

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
                if(j < x)
                    printf(" ");
                else
                    printf("*");
            }
        }
        printf("\n");
    }

    getchar();
    system("clear");

    angel = M_PI*angel/180;
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
