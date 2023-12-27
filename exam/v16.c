#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main()
{
    char str1[] = "Hello world!\n";
    char str2[] = "It`s a cruel place...";

    char* str11 = (char*) malloc(strlen(str1) * sizeof(char));
    //strcpy(str11, str1);

    //str11 = (char*) realloc(str11, (strlen(str1) + strlen(str2)) * sizeof(char));

    strcat(str1, str2);

    printf("%s", str1);
}
