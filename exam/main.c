#include <stdio.h>
#include <stdlib.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int main()
{
    int aSize, bSize;
    CHECK_INPUT(scanf("%d", &aSize))
    CHECK_INPUT(scanf("%d", &bSize))

    int* A = malloc(aSize * sizeof(int));
    int* B = malloc(bSize * sizeof(int));

    int* C = malloc(max(aSize, bSize) * sizeof(int));

    int sizeC = 0;

    for(int i = 0; i < aSize; i++)
    {
        CHECK_INPUT(scanf("%d", A+i));
    }

    for(int i = 0; i < bSize; i++)
    {
        CHECK_INPUT(scanf("%d", B+i));
    }

    for(int i = 0; i < aSize; i++)
    {
        int amountA = 0;
        int amountB = 0;

        for(int j = 0; j < bSize; j++)
        {
            if(A[i] == B[j])
                amountB++;
        }

        if(amountB == 1)
        {
            for(int j = 0; j < aSize; j++)
            {
                if(A[i] == A[j])
                    amountA++;
            }
        }

        if(amountA == 1 && amountB == 1)
        {
            C[sizeC] = A[i];
            printf("\n%d", C[sizeC]);
            sizeC++;
        }
    }

    C = realloc(C, sizeC * sizeof(int));

    return 0;
}
