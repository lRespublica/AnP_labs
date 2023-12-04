#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct
{
    unsigned int size;
    double** data;
} matrix;

void initMatrix(matrix* mat)
{
    if(mat->size == 0)
        return;

    mat->data = malloc(mat->size * sizeof(double*));
    for(int i = 0; i < mat->size; i++)
        mat->data[i] = malloc(mat->size * sizeof(double));
}


void copyMatrix(matrix* from, matrix* to)
{
    to->size = from->size;
    initMatrix(to);
    for(int i = 0; i < from->size; i++)
    {
        for(int j = 0; j < from->size; j++)
        {
            to->data[i][j] = from->data[i][j];
        }
    }
}

void printMatrix(matrix mat)
{
    for(int i = 0; i < mat.size; i++)
    {
        for(int j = 0; j < mat.size; j++)
            printf("%10.2lf ", mat.data[i][j]);
        printf("\n");
    }
}

void genRandomMatrix(matrix* mat)
{
    for(int i = 0; i < mat->size; i++)
    {
        for(int j = 0; j < mat->size; j++)
            mat->data[i][j] = ((rand()%32768) - ((RAND_MAX)%32768)/2);
    }
}

void sumColl(matrix* in, int dest, int from, double arg)
{
    for(int i = 0; i < in->size; i++)
        in->data[dest][i] += in->data[from][i] * arg; 
}

matrix getUpperTriangle(matrix source)
{
    matrix res;
    copyMatrix(&source, &res);
    double** data = res.data;
    int size = res.size;

    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
            sumColl(&res, j, i, (-data[j][i])/data[i][i]); 
    }

    return res;
}

int main()
{
    srand(time(NULL));

    matrix mat;

    mat.size = 5;

    initMatrix(&mat);
    genRandomMatrix(&mat);
    printMatrix(mat);

    matrix newMat = getUpperTriangle(mat);
    printf("\n");

    printMatrix(newMat);
}
