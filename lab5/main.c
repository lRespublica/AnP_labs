#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int inputArray(int** arr, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            CHECK_INPUT(scanf("%d", &(arr[i][j])))
    }
    
    return 0;
}

void printArray(int** arr, int m, int n)
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);

        printf("\n");
    }
}

int findUpperMax(int** arr, int m, int n)
{
    int max = INT_MIN;
    for(int i = 0; i < m; i++)
    {
        for(int j = i; j < n; j++)
        {
            if(arr[i][j] > max)
                max = arr[i][j];
        }
    }
    return max;
}

int findLowerMin(int** arr, int m, int n)
{
    int min = INT_MAX;
    for(int i = 0; i < m; i++)
    {
        for(int j = i; j > 0; j--)
        {
            if(arr[i][j] < min)
                min = arr[i][j];
        }
    }
    return min;
}

int solveTask(int** arr, int m, int n)
{
    return findUpperMax(arr, m, n) * findLowerMin(arr, m, n);
}

int main()
{
    int m, n;

    printf("Введите размер матрицы\n");
    CHECK_INPUT(scanf("%d", &m));
    CHECK_INPUT(scanf("%d", &n));

    if (m < 2 || m > 10 || n < 2 || n > 10)
        return 1;

    int** arr = alloca(sizeof(int*) * m);
    for(int i = 0; i < m; i++)
    {
        arr[i] = alloca(sizeof(int) * n);
    }

    if(inputArray(arr, m, n) == 1)
        return 1;

    int value = solveTask(arr, m, n);
    printf("\nРезультат: %d\n", solveTask(arr, m, n));
}
