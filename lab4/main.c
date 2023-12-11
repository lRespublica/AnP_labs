#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

double findMaxTask(double* arr, int size, double X, double Y)
{
    double max = -DBL_MAX;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] >= max && arr[i] <=Y)
            max = arr[i];
    }
    return max;
}

double findAverageTask(double* arr, int size)
{
    double total = 0;
    int amount = 0;

    int minI;
    double minElement = DBL_MAX;

    for(int i = 0; i < size; i++)
    {
        if(arr[i] < minElement)
        {
            minI = i;
            minElement = arr[i];
        }
    }

    for(int i = minI+1; i < size; i++)
    {
        total += arr[i];
        amount ++;
    }

    return total/amount;
}

int main()
{
    int k;
    double X, Y;

    printf("Введите размер массива\n");
    CHECK_INPUT(scanf("%d", &k));
    printf("Введите минимальный и максимальный элемент\n");
    CHECK_INPUT(scanf("%lf", &X));
    CHECK_INPUT(scanf("%lf", &Y));
    
    if (X>Y)
        return 1;

    double arr[k];

    printf("Введите элементы массива\n");
    for(int i = 0; i < k; i++)
        CHECK_INPUT(scanf("%lf", arr+i));

    double taskMax = findMaxTask(arr, k, X, Y);
    if(taskMax != -DBL_MAX)
        printf("Максимальный элемент массива, находящийся в промежутке [%lf;%lf] = %lf\n", X, Y, taskMax);
    else
        printf("Не удалось найти максимальный элемент, соответствующий условию задачи\n");

    double average = findAverageTask(arr, k);
    if(average != average)
        printf("Не удалось найти среднее арифметическое\n");
    else
        printf("Среднее арифметическое, соответсвующее условию = %lf\n", average);
}
