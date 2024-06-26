#include "stdio.h"
#include "stdlib.h"
#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int main()
{
    int size;

    printf("Enter size: ");
    CHECK_INPUT(scanf("%d", &size));

    if(size < 0)
        return 1;

    int* arr = malloc(size * sizeof(int));
    unsigned int max = 0;

    for(int i = 0; i < size; i++)
        CHECK_INPUT(scanf("%d", arr+i));

    for(int i = 0; i < size; i++)
    {
        unsigned int counter = 0;
        for(int j = i; j < size; j++)
        {
            if(arr[i] == arr[j])
                counter++;
        }

        if(counter > max)
            max = counter;
    }

    printf("Max count: %u", max);

    free(arr);
}
