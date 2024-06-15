#include "crc32.c"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

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

typedef struct hashTableNode{
   record* value;
   struct hashTableNode* next;
} hashTableNode;

typedef struct {
    hashTableNode** arr;
    unsigned int size;

    unsigned int elementsCount;
} recordsTable;

hashTableNode* createNode(const record* value)
{
    hashTableNode* newNode = malloc(sizeof(hashTableNode));
    
    newNode->value = malloc(sizeof(*value));
    
    newNode->value->flight = value->flight;
    newNode->value->baggage = value->baggage;
    newNode->value->seat = value->seat;

    newNode->value->date.day = value->date.day;
    newNode->value->date.year = value->date.year;
    newNode->value->date.month = value->date.month;

    strncpy(newNode->value->name, value->name, 32);

    newNode->next = NULL;

    return newNode;
}

hashTableNode* createNodeViaPointer(record* value)
{
    hashTableNode* newNode = malloc(sizeof(hashTableNode));

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

hashTableNode* removeNode(hashTableNode* curNode)
{
    hashTableNode* next = curNode->next;

    free(curNode);
    return next;
}

void appendNode(hashTableNode* curNode, const record* appendValue)
{
    while(curNode->next != NULL)
        curNode = curNode->next;
    
    curNode->next = createNode(appendValue);
}

void appendNodeViaPointer(hashTableNode* curNode, record* appendValue)
{
  while(curNode->next != NULL)
      curNode = curNode->next;

  curNode->next = createNodeViaPointer(appendValue);
}


recordsTable* createClearTable(const unsigned int size)
{
    if (size == 0)
        return NULL;

    recordsTable* table = malloc(sizeof(recordsTable));

    table->size = size;
    table->elementsCount = 0;
    table->arr = malloc(sizeof(hashTableNode) * size);

    for(int i = 0; i < size; i++)
        table->arr[i] = NULL;

    return table;
}

hashTableNode** getRecordsByHash(const recordsTable* table, const unsigned int hash)
{
    return table->arr + (hash % table->size);
}

void rehashTable(recordsTable* table);

void addTableElement(recordsTable* table, const record* record )
{
    unsigned int crc = crc32((const unsigned char*) record, sizeof(*record));  

    hashTableNode** tableRecord = getRecordsByHash(table, crc);

    if (*tableRecord == NULL)
        *tableRecord = createNode(record);
    else
        appendNode(*tableRecord, record);

    table->elementsCount++;
    
    if(table->elementsCount > table->size * 4)
        rehashTable(table);
}

void addTableElementViaPointer(recordsTable* table, record* record )
{
    unsigned int crc = crc32((const unsigned char*) record, sizeof(*record));

    hashTableNode** tableRecord = getRecordsByHash(table, crc);

    if (*tableRecord == NULL)
        *tableRecord = createNodeViaPointer(record);
    else
        appendNodeViaPointer(*tableRecord, record);

    table->elementsCount++;
}

void rehashTable(recordsTable* table)
{
    hashTableNode** origArr = table->arr;
    unsigned int origSize = table->size;

    table->size = origSize * 4;
    table->elementsCount = 0;
    table->arr = malloc(sizeof(hashTableNode*) * table->size);

    for(int i = 0; i < origSize; i++)
    {
        hashTableNode* curNode = origArr[i];
        while (curNode != NULL)
        {
            addTableElementViaPointer(table, curNode->value);

            curNode = curNode->next;
        }
    }
}

void printRecord(const record* record, FILE* dest)
{
    fprintf(dest, "Flight: %d\n", record->flight);

    fprintf(dest, "Date: %d.%d.%d\n", record->date.day, record->date.month, record->date.year);

    fprintf(dest, "Name: %s\n", record->name);
    fprintf(dest, "Seat: %d\n", record->seat);
    fprintf(dest, "Baggage: %d\n", record->baggage);
}

void printTable(const recordsTable* table)
{
    for(int i = 0; i < table->size; i++)
    {
        hashTableNode* curNode = table->arr[i];
        printf("Hash: %x\n", i);
        while (curNode != NULL)
        {
            printRecord(curNode->value, stdout);
            printf("\n");

            curNode = curNode->next;
        }
        printf("\n");
    }
}
