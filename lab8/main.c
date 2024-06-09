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

void skipLine()
{
    char c;
    do
    {
        c = getchar();
    } while(c != EOF && c != '\n');
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

int checkDateNumbers(int day, int month, int year)
{
    if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1909)
        return 0;

    if(day > 30 && (month != 1 && month != 3 && month != 5 && month != 7 && month != 8 && month != 10 && month != 12))
        return 0;

    if(day > 29 && month == 2)
        return 0;

    if(day > 28 && month == 2 && !(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)))
        return 0;

    return 1;
}

int verifyDate(char* date)
{
    if(strlen(date) != 11)
        return 0;

    int day = atoi(strtok(date, "."));
    int month = atoi(strtok(NULL, "."));
    int year = atoi(strtok(NULL, "."));

    if (checkDateNumbers(day, month, year) == 0)
    {
        printf("Некорректная дата\n");
        return 0;
    }

    return 1;
}

record inputRecord()
{
    record rec;
    char BUFF[64];

    printf("Введите номер рейса: ");
    scanf(" %u", &rec.flight);
    skipLine();

    do 
    {
        printf("Введите дату в формате (дд.мм.гггг): ");
        fgets(BUFF, 64, stdin);
    } while(verifyDate(BUFF) != 1);

    printf("%d", strlen(BUFF));

    printf("Введите имя: ");
    

    return rec;
}

void appendDB(dataStruct* data, record rec)
{
    data->size += 1;
    data->data = realloc(data->data, data->size);

    data->data[data->size] = rec; 
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

    inputRecord();

    fclose(DB);
    saveDB(data);
    return 0;
}
