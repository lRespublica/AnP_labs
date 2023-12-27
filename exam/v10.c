#include <stdio.h>

void func1(int val1, int val2)
{
    val1 -= val2;

    printf("%d %d\n", val1, val2);
}

void func2(int val1, int* val2)
{
    *val2 -= val1;

    printf("%d %d\n", val1, *val2);
}

void func3(int* val1, int val2)
{   
    *val1 -= val2;

    printf("%d %d\n", *val1, val2);
}

int main()
{
    int val1 = 10;
    int val2 = 42;

    printf("%d %d\n", val1, val2);

    func1(val1, val2);
    func2(val1, &val2);
    func3(&val1, val2);

    printf("%d %d\n", val1, val2);
}
