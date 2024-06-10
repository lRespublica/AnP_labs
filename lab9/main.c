#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define DEBUG 0

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

void printRecordsArray(record** records, int amount, FILE* dest)
{
    for(int i = 0; i < amount; i++)
    {
        fprintf(dest, "Record %d\n", i);
        printRecord(records[i], dest);
        fprintf(dest, "\n");
    }   
}

record** clearRecordsArray(record** records, int amount)
{
    for(int i = 0; i < amount; i++)
        free(records[i]);

    free(records);
    return NULL;
}

record** copyRecordsArray(record** records, int amount)
{
    record** genRecords = malloc(sizeof(record*) * amount);

    for(int i = 0; i < amount; i++)
    {
        genRecords[i] = malloc(sizeof(record));

        genRecords[i]->flight = records[i]->flight;
        genRecords[i]->baggage = records[i]->baggage;
        genRecords[i]->seat = records[i]->seat;

        genRecords[i]->date.day = records[i]->date.day;
        genRecords[i]->date.year = records[i]->date.year;
        genRecords[i]->date.month = records[i]->date.month;

        strncpy(genRecords[i]->name, records[i]->name, 32);
    }

    return genRecords;
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

    if(order == DESCENDING && equalFlag == 0)
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

record** generateRandomRecords(int amount)
{
    if(DEBUG)
    {
        fprintf(stderr, "################\n");
        fprintf(stderr, "Begin of generation\n\n");
    }

    record** randRecords = malloc(sizeof(record*) * amount);

    for(int i = 0; i < amount; i++)
    {
        randRecords[i] = malloc(sizeof(record));

        randRecords[i]->flight = rand() % 65536;
    
        randRecords[i]->date.year = (rand() % 115) + 1909;
        randRecords[i]->date.month = (rand() % 12) + 1;
        randRecords[i]->date.day = (rand() % 28) + 1;

        randRecords[i]->seat = rand() % 255;
        randRecords[i]->baggage = rand() % 255;

        int nameLen[2] = {rand() % 15 + 1, rand() % 15 + 1};

        for(int j = 0; j < nameLen[0] + nameLen[1] + 1; j++)
        {
            if (j == 0 || j == nameLen[0] + 1)
                randRecords[i]->name[j] = (rand() % 26) + 65;
            else if(j == nameLen[0])
                randRecords[i]->name[j] = ' ';
            else
                randRecords[i]->name[j] = (rand() % 26) + 97;
        }

        if(DEBUG)
        {
            fprintf(stderr, "Record %d\n", i);
            printRecord(randRecords[i], stderr);
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

int isSorted(record** records, int amount, sortOrder order)
{
    int isSorted = 1;

    for(int i = 0; i < amount - 1; i++)
    {
        if(compareRecord(records[i], records[i+1], order) == 1)
        {
            isSorted = 0;
            break;
        }
    }

    return isSorted;
}

void bubbleSort(record** records, int amount, sortOrder order)
{
    for(int i = amount; i >= 0; i--)
    {
        int continueFlag = 0;
        for(int j = 1; j < i; j++)
        {
            if(compareRecord(records[j - 1], records[j], order) == 1)
            {
                record* tmp = records[j];
                records[j] = records[j - 1];
                records[j-1] = tmp;

                continueFlag = 1;
            }
        }
        if(continueFlag == 0)
            break;
    }
}

void coctailSort(record** records, int amount, sortOrder order)
{
    int left = 0;
    int right = amount - 1;
    int continueFlag = 1;

    while(left < right && continueFlag != 0)
    {
        continueFlag = 0;

        for(int j = left; j < right; j++)
        {
            if(compareRecord(records[j], records[j + 1], order) == 1)
            {
                record* tmp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = tmp;

                continueFlag = 1;
            }
        }

        if(continueFlag == 0)
            break;
    
        right--;

        for(int j = right; j > left; j--)
        {
            if(compareRecord(records[j], records[j - 1], order) == 0)
            {
                record* tmp = records[j];
                records[j] = records[j - 1];
                records[j - 1] = tmp;

                continueFlag = 1;
            }
        }

        left++;
    }
}

void quickSort(record** records, int amount, sortOrder order)
{
    record* pivot; 
    
    int left = 0;
    int right = amount - 1;

    pivot = records[left];
    while (left < right)
    {
        while ((compareRecord(records[right], pivot, order) == 1) && (left < right))
            right--;
        if (left != right)
        {
            records[left] = records[right];
            left++;
        }
        while ((compareRecord(records[left], pivot, order) == 0) && (left < right))
            left++;
        if (left != right)
        {
            records[right] = records[left];
            right--; 
        }
    }
    records[left] = pivot; 
    
    if (left > 0 )
        quickSort(records, left, order);
    if (left < amount)
        quickSort(records + left + 1, amount - left - 1, order);
}

int main()
{
    srand(time(NULL));

    #define amountTypesLen 7

    int amountTypes[amountTypesLen] = {100, 1000, 5000, 10000, 20000, 50000, 100000}; 

    struct timespec start, end;
    int amount = 10;
    int input;
    sortOrder order = ASCENDING;

    printf("Enter direction:\n 1. Ascending\n 2. Descending\n> ");
    scanf("%d", &input);

    switch(input)
    {
        case 1:
            order = ASCENDING;
            break;
        case 2:
            order = DESCENDING;
            break;
        default:
            printf("\nUnrecognized option!\n");
            return 1;
            break;
    }

    input = 0;

    printf("\nEnter amount:\n");
    for(int i = 0; i < amountTypesLen; i++)
        printf(" %d. %d\n", i+1, amountTypes[i]);
    printf("> ");
    scanf("%d", &input);

    if(input >= 1 && input <= amountTypesLen)
    {
        amount = amountTypes[input - 1];
    }
    else
    {
        printf("\nUnrecognized option!\n");
        return 1;
    }

    input = 0;

    printf("\nEnter sort type:\n 1. Bubble sort\n 2. Cocktail sort\n 3. Quick sort\n> ");
    scanf("%d", &input);

    if(input < 1 || input > 3)
    {
          printf("\nUnrecognized option!\n");
          return 1;
    }  


    record** generatedRecords = generateRandomRecords(amount);

    printf("\n");
    switch(input)
    {
        case 1:
            printf("We use bubble sort\n");
            
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            bubbleSort(generatedRecords, amount, order);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            
            break;
        case 2:
            printf("We use cocktail sort\n");
            
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            coctailSort(generatedRecords, amount, order);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            
            break;
        case 3:
            printf("We use quick sort\n");
            
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            quickSort(generatedRecords, amount, order);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            
            break;

        default:              
            printf("\nUnrecognized option!\n");                                 
            return 1;
    }
    int tookTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    printf("Is array sorted: %d\n", isSorted(generatedRecords, amount, order));
    printf("It took %d mcs\n", tookTime);
}
