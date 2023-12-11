#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int inputArray(float* arr, int size)
{
    for(int i = 0; i < size; i++)
        CHECK_INPUT(scanf("%f", &(arr[i])))

    return 0;
}

void printArray(float* arr, int size)
{
    for(int i = 0; i < size; i++)
        printf("%f ", arr[i]);
}

void moveElements(float* arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i] != arr[i])
        {
            for(int j = i; j < size - 1; j++)
            {
                arr[j] = arr[j+1];
                arr[j+1] = NAN;
            }
        }
    }
}

float* solveTask(float* arr, int *distSize)
{
    int counter = 0;

    int size = *distSize;
    float max = arr[0];

    for(int i = 0; i < size; i += 2)
    {
        if(arr[i] > max)
            max = arr[i];
    }

    for(int i = 1; i < size; i+= 2)
    {
        if(arr[i] > max)
        {
            arr[i] = NAN;
            counter++;
        }
    }
    
    moveElements(arr, size);
    printArray(arr, size);
    printf("\n\n");

    (*distSize) -= counter;

    return (float*)realloc(arr, *distSize);
}

int main()
{
    int size;

    printf("Введите размер массива\n");
    CHECK_INPUT(scanf("%d", &size));

    float* arr = malloc(sizeof(int*) * size);

    if(inputArray(arr, size) == 1)
        return 1;

    arr = solveTask(arr, &size);
    printArray(arr, size);
}
