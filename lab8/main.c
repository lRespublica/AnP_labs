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
        char BUFF[256];
        char* curStr;
        int curStrLen;
        int length = 0;
        do
        {
            BUFF[length] = fgetc(DB);
            length++;
        } while (BUFF[length-1] != '\n');
        
        data.data[i].flight = atoi(strtok(BUFF, "\t"));

        curStr = strtok(NULL, "\t");
        curStrLen = strlen(curStr);
        data.data[i].date = malloc(curStrLen);
        strcpy(data.data[i].date, curStr);
        
        curStr = strtok(NULL, "\t");
        curStrLen = strlen(curStr);
        data.data[i].name = malloc(curStrLen);
        strcpy(data.data[i].name, curStr);

        data.data[i].seat = atoi(strtok(NULL, "\t"));
        data.data[i].baggage = atoi(strtok(NULL, "\t"));
    }

    return data;
}

void printDB(dataStruct data)
{
    for(int i = 0; i < data.size; i++)
    {
        printf("%u\t%s\t%s\t%u\t%u\n", data.data[i].flight, data.data[i].date,
                data.data[i].name, data.data[i].seat, data.data[i].baggage);
    }
}

void saveDB(dataStruct data)
{
    FILE* DB = fopen("./flight.db", "w");
    
    for(int i = 0; i < data.size; i++)
    {
         fprintf(DB, "%u\t%s\t%s\t%u\t%u\n", data.data[i].flight, data.data[i].date,
                data.data[i].name, data.data[i].seat, data.data[i].baggage);
    }
}

int main()
{
    FILE* DB = initDB();
    dataStruct data = getInitData(DB);
    printDB(data);


    fclose(DB);
    saveDB(data);
    return 0;
}
