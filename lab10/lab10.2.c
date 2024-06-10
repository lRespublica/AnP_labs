#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

typedef struct wordNode {
    char word[32];
    struct wordNode* next;
    struct wordNode* past;
} wordNode;

wordNode* createNode(const char* val)
{
    wordNode* curNode = malloc(sizeof(wordNode));

    curNode->next = NULL;
    curNode->past = NULL;

    strncpy(curNode->word, val, 31);
    curNode->word[31] = '\0';

    return curNode;
}

void appendNode(wordNode* parent, const char* val)
{
    if(parent == NULL)
        return;

    wordNode* curNode = parent;

    while(curNode->next != NULL)
        curNode = curNode->next;

    curNode->next = createNode(val);
    curNode->next->past = curNode;
}

wordNode* removeNode(wordNode* curNode)
{
    if(curNode == NULL)
        return NULL;

    wordNode* parent = curNode->past;
    wordNode* child = curNode->next;

    free(curNode);

    if(parent != NULL)
        parent->next = child;
    
    if(child != NULL)
        child->past = parent;

    return child;
}

wordNode* copyList(wordNode* orig)
{
    if (orig == NULL)
        return NULL;

    while(orig->past != NULL)
        orig = orig->past;

    wordNode* newList = createNode(orig->word);
    orig = orig->next;

    while(orig != NULL)
    {
        appendNode(newList, orig->word);
        
        orig = orig->next;
    }

    return newList;
}

void deleteNonUniqWords(wordNode* curNode)
{
    if(curNode == NULL)
        return;

    while(curNode->past != NULL)
        curNode = curNode->past;
    
    while(curNode != NULL)
    {
        wordNode* iterNode = curNode->next;

        while(iterNode != NULL)
        {
            if(strcmp(iterNode->word, curNode->word) == 0)
            {
                wordNode* tmpNode = iterNode->past;

                removeNode(iterNode);
                iterNode = tmpNode;
            }
            iterNode = iterNode->next;
        }

        curNode = curNode->next;
    }
}

void printAllWords(const wordNode* curNode)
{
    if(curNode == NULL)
        return;

    while(curNode->past != NULL)
        curNode = curNode->past;

    while(curNode != NULL) 
    {
        printf("%s ", curNode->word);
        curNode = curNode->next;
    }
}

int main () 
{
    char input[64];
    struct wordNode* list = NULL;

    printf("Enter string:\n");

    while (scanf("%s", input) == 1) 
    {
        int len = strlen(input);

        int breakFlag = 0;

        for (int i = 0; i < len; i++) 
        {
            if (!isalpha(input[i]) && input[i] != ' ') 
            {
                if (input[i] == '.') 
                {
                    len = i;
                    input[len] = '\0';
                    breakFlag = 1;
                    break;
                } 
                else 
                {
                    fprintf(stderr, "ERROR: '%c' is not alpha\n", input[i]);
                    return 1;
                }
            }
        }

        if (len != 0) 
        {
            if (list == NULL)
                list = createNode(input);
            else 
                appendNode(list, input);
        }

        if (breakFlag == 1 || len == 0) {
            break;
        }
    }

    wordNode* clearedList = copyList(list);
    deleteNonUniqWords(clearedList);

    printf("\nRESULT:\nOriginal tokens:\n");
    printAllWords(list);

    printf("\n\nCleared and only uniq words:\n");
    printAllWords(clearedList);

    printf("\n");

    return 0;
}
