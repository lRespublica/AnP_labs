#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define DEBUG 1

typedef struct{
    unsigned int year;
    unsigned int month;
    unsigned int day;
} date;

typedef struct{
    unsigned int flight;
    date date;
    char name[32];
    unsigned int seat;
    unsigned int baggage;
} record;

typedef enum {ASCENDING = 0, DESCENDING, EQUAL} sortOrder;

// Return 1 if first date >=(<=) then second date
int compareDate(const date* date1, const date* date2, sortOrder order)
{
    int result = 0;

    // First iteration - year comparision
    // Second - month
    // Third - day
    // If all are equal - then date1 == date2
    for(int i = 0; i < 3; i++)
    {
        unsigned int val1 = *((unsigned int*)date1 + i);
        unsigned int val2 = *((unsigned int*)date2 + i);

        if(val1 == val2)
        {
            result = 1;
            continue;
        }
        else
        {
            if(order == ASCENDING)
                result = (val1 >= val2);
            else if(order == DESCENDING)
                result = (val1 <= val2);
            else if(order == EQUAL)
                result = 0;

            break;
        }
    }

    return result;
}

void printRecord(const record* record, FILE* dest)
{
    fprintf(dest, "Flight: %d\n", record->flight);
    
    fprintf(dest, "Date: %d.%d.%d\n", record->date.day, record->date.month, record->date.year);

    fprintf(dest, "Name: %s\n", record->name);
    fprintf(dest, "Seat: %d\n", record->seat);
    fprintf(dest, "Baggage: %d\n", record->baggage);
}

int compareRecord(const record* record1, const record* record2, sortOrder order)
{
    int result = 0;
    int equalFlag = 0;

    if(DEBUG)
    {
        fprintf(stderr, "###################\n");
        printRecord(record1, stderr);
        printf("\n");
        printRecord(record2, stderr);
        printf("\n");
    }

    if(record1->flight != record2->flight)
    {
        if(DEBUG)
            fprintf(stderr, "FLIGHT!\n");

        result = (record1->flight >= record2->flight);
    }

    else if(compareDate(&record1->date, &record2->date, EQUAL) == 0)
    {
        if(DEBUG)
            fprintf(stderr, "DATE!\n");

        result = compareDate(&record1->date, &record2->date, ASCENDING);
    }

    else if(strcmp(record1->name, record2->name) != 0)
    {
        if(DEBUG)
            fprintf(stderr, "NAME!\n");

        result = strcmp(record1->name, record2->name);

        if(result < 0)
            result = 0;
    }

    else if(record1->seat != record2->seat)
    {
        if(DEBUG)
            fprintf(stderr, "SEAT!\n");

        result = (record1->seat >= record2->seat);
    }

    else if(record1->baggage != record2->baggage)
    {
        if(DEBUG)
            fprintf(stderr, "BAGGAGE!\n");

        result = (record1->baggage >= record2->baggage);
    }

    else
    {
        if(DEBUG)
            fprintf(stderr, "THEY ARE EQUAL!!!\n");

        result = 1;
        equalFlag = 1;
    }

    if(order == DESCENDING)
        result = !result;
    else if(order == EQUAL)
        result = equalFlag;

    if(DEBUG)
    {
        fprintf(stderr, "Comparision value: %d\n", result); 
        fprintf(stderr, "###################\n\n");
    }

    return result;
}

record* generateRandomRecords(int amount)
{
    if(DEBUG)
    {
        fprintf(stderr, "################\n");
        fprintf(stderr, "Begin of generation\n\n");
    }

    record* randRecords = malloc(sizeof(record) * amount);

    for(int i = 0; i < amount; i++)
    {
        randRecords[i].flight = rand() % 65536;
    
        randRecords[i].date.year = (rand() % 115) + 1909;
        randRecords[i].date.month = (rand() % 12) + 1;
        randRecords[i].date.day = (rand() % 28) + 1;

        randRecords[i].seat = rand() % 255;
        randRecords[i].baggage = rand() % 255;

        int nameLen[2] = {rand() % 15 + 1, rand() % 15 + 1};

        for(int j = 0; j < nameLen[0] + nameLen[1] + 1; j++)
        {
            if (j == 0 || j == nameLen[0] + 1)
                randRecords[i].name[j] = (rand() % 26) + 65;
            else if(j == nameLen[0])
                randRecords[i].name[j] = ' ';
            else
                randRecords[i].name[j] = (rand() % 26) + 97;
        }

        if(DEBUG)
        {
            fprintf(stderr, "Record %d\n", i);
            printRecord(&randRecords[i], stderr);
            fprintf(stderr, "\n\n");
        }
    }

    if(DEBUG)
    {
        fprintf(stderr, "END OF GENERATION\n");
        fprintf(stderr, "################\n\n");
    }

    return randRecords;
}

int main()
{
    srand(time(NULL));

    int amount = 10;

    record* generatedRecords = generateRandomRecords(amount);

    date tmpDate1 = {2010, 4, 4}; 
    date tmpDate2 = {2012, 3, 5}; 
    
    record tmpRecord1 = {10, tmpDate1, "Mr. Mark Knopfler", 11, 32};
    record tmpRecord2 = {10, tmpDate1, "Mrs. Misery", 10, 2};
}
