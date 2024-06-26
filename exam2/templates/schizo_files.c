#include "stdio.h"

int main()
{
    FILE* writeFile = fopen("test_file.txt", "r+");
    FILE* readFile = fopen("read_file.txt", "r");

    int tmp;

    while(!feof(writeFile))
        fgetc(writeFile);

    int origLen = ftell(writeFile);

    while(fscanf(readFile, "%d", &tmp) == 1)
    {
        fprintf(writeFile, "%d ", tmp);
    }

    int modifiedLen = ftell(writeFile);
    for(int i = 0; i < origLen; i++)
    {
        fseek(writeFile, i, SEEK_SET);
        char tmpChar = fgetc(writeFile);
        fseek(writeFile, 0, SEEK_END);
        fputc(tmpChar, writeFile);
    }

    rewind(writeFile);
    for(int i = 0; i < origLen; i++)
    {
        fputc('\0', writeFile);
    }

    fclose(writeFile);
    fclose(readFile);
}
