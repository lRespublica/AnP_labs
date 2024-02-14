#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_INPUT(flag) if (!flag || feof(stdin)) {printf("Incorrect input\n"); return 1;};

typedef struct{
    unsigned int flight;
    char* date;
    char* name;
    unsigned int seat;
    unsigned int baggage;
} record;

typedef struct {
    unsigned int size;
    record* data;
} dataStruct;

void criticalError(char* message)
{
    fprintf(stderr, "%s", message);
    fprintf(stderr, "\n");
    exit(1);
}

FILE* initDB()
{
    FILE* DB = fopen("./flight.db", "r");
    if (DB == NULL)
    {
        DB = fopen("./flight.db", "w");
        fclose(DB);
        FILE* DB = fopen("./flight.db", "r");
        if(DB == NULL)
        {
            criticalError("Can`t open DB file");
        }
    }
    return DB;
}

dataStruct getInitData(FILE* DB)
{
    char BUFF[256];
    dataStruct data;
    data.size = 0;
    while(!feof(DB))
    {
        if(fgetc(DB) == '\n')
            data.size++;
    }
    rewind(DB);

    if(data.size != 0)
        data.data = malloc(data.size * sizeof(record));

    for(int i = 0; i < data.size; i++)
    {
        char* curStr;
        int curStrLen;
        int length = 0;
        do
        {
            BUFF[length] = fgetc(DB);
            length++;
        } while (BUFF[length-1] != '\n');
        
        strtok(BUFF, "\t");
        
        data.data[i].flight = atoi(strtok(NULL, "\t"));

        curStr = strtok(NULL, "\t");
        curStrLen = strlen(curStr);
        data.data[i].date = malloc(curStrLen);
        strcpy(curStr, data.data[i].date);
        
        curStr = strtok(NULL, "\t");
        curStrLen = strlen(curStr);
        data.data[i].name = malloc(curStrLen);
        strcpy(curStr, data.data[i].name);

        data.data[i].seat = atoi(strtok(NULL, "\t"));
        data.data[i].baggage = atoi(strtok(NULL, "\t"));
    }

    return data;
}

int main()
{
    FILE* DB = initDB();
    getInitData(DB);
}
