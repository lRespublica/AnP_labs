#include "hashtable.c"
#include "time.h"

#define DEBUG 0

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

int main()
{
    srand(time(NULL));

    int size = 1000;
    record** randRecords = generateRandomRecords(size);

    recordsTable* table = createRecordsTableFromArray(randRecords, size);

    free(randRecords);
    randRecords = generateRandomRecords(size*10);

    for(int i = 0; i < size*10; i++)
        addTableElement(table, randRecords[i]);
    
    for(int i = 0; i < rand() % 20 + 1; i++)
    {
        addTableElement(table, randRecords[size]);
    }

    printRecordByName(table, randRecords[size]->name);
    printRecordByName(table, "Mr. Mark Knopler");
}
