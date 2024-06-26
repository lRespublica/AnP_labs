#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct sNode
{
    char* val;
    struct sNode* next;
} sNode;

sNode* appendVal(sNode* node, char* val)
{
    if (node == NULL)
    {
        node = malloc(sizeof(sNode));
        node->val = val;
        node->next = NULL;
        return node;
    }

    sNode* curNode = node;

    while(curNode->next != NULL)
        curNode = curNode->next;

    curNode->next = malloc(sizeof(sNode));
    curNode->next->val = val;
    curNode->next->next = NULL;

    return node;
}

sNode* removeNode(sNode* dest)
{
    sNode* saveNode = dest->next;

    free(dest);
    return saveNode;
}

sNode* removeWord(sNode* dest, char* word)
{
    if (dest == NULL)
        return NULL;

    while(strcmp(dest->val, word) == 0)
    {
        dest = removeNode(dest);
    }

    sNode* curNode = dest->next;
    sNode* pastNode = dest;

    while(curNode != NULL)
    {
        while (strcmp(curNode->val, word) == 0)
        {
            curNode = removeNode(curNode);
            if(curNode == NULL)
                break;
        }

        pastNode->next = curNode;

        if(curNode == NULL)
            break;

        curNode = curNode->next;
        pastNode = pastNode->next;
    }

    return dest;
}

void printList(sNode* node)
{
    while(node != NULL)
    {
        printf("%s ", node->val);
        node = node->next;
    }
}

int main()
{
    char buff[128];

    fgets(buff, 100, stdin);
    printf("%s\n", buff);
    
    sNode* tokensList = appendVal(NULL, strtok(buff, " ,."));
    
    while(1)
    {
        char* token = strtok(NULL, " ,.\n");
        
        if(token == NULL)
            break;

        appendVal(tokensList, token);
    }
    printList(tokensList);
    printf("\n");

    tokensList = removeWord(tokensList, "dear");

    printList(tokensList);
}
