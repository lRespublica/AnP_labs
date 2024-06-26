#include "stdio.h"
#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int main()
{
    int size;

    printf("Enter size: ");
    CHECK_INPUT(scanf("%d", &size));

    if(size < 0)
        return 1;

    int arr[size];

    for(int i = 0; i < size; i++)
        CHECK_INPUT(scanf("%d", arr+i));

    for (int i = 0; i < size - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[max])
            {
                max = j;
            }
        }
        if (max != i)
        {
            int tmp = arr[i];
            arr[i] = arr[max];
            arr[max] = tmp;
        }
    }

    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}
