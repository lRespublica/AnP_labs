#include "stdlib.h"
#include "stdio.h"
#include "time.h"

typedef struct {
    int coef;
    int degree;
} monom;

typedef struct polyNode{
    monom val;
    struct polyNode* next;
} polyNode;

void printMonom(const monom* value)
{
    printf("%d*x^(%d)", value->coef, value->degree);
}

void printPoly(const polyNode* curNode)
{
    while(curNode != NULL)
    {
        printMonom(&curNode->val); 

        curNode = curNode->next;
        if(curNode != NULL)
        {
            printf(" + ");
        }
    }

    printf("\n");
}

polyNode* createNode(const monom* value)
{
    polyNode* newNode = malloc(sizeof(polyNode));
    
    newNode->val.coef = value->coef;
    newNode->val.degree = value->degree;
    newNode->next = NULL;

    return newNode;
}

polyNode* removeNode(polyNode* curNode)
{
    polyNode* next = curNode->next;

    free(curNode);
    return next;
}

void appendNode(polyNode* curNode, const monom* appendValue)
{
    while(curNode->next != NULL)
        curNode = curNode->next;
    
    curNode->next = createNode(appendValue);
}

void copyNode(polyNode* dest, const polyNode* orig)
{
    dest->val.coef = orig->val.coef;
    dest->val.degree = orig->val.degree;
}

polyNode* appendList(polyNode* dest, const polyNode* orig)
{
    polyNode* curNode;
    const polyNode* nextNode;

    if(orig == NULL)
        return NULL;

    if(dest != NULL)
    {
        curNode = dest;
        
        nextNode = orig; 
    }
    if(dest == NULL)
    {
        curNode = malloc(sizeof(polyNode));

        copyNode(curNode, orig);

        nextNode = orig->next;
    }

    while(nextNode != NULL)
    {
        appendNode(curNode, &nextNode->val);

        nextNode = nextNode->next;
    }

    return curNode;
}

polyNode* clearFromZeroes(polyNode* dest)
{
    if (dest == NULL)
        return NULL;

    while(dest->val.coef == 0)
    {
        dest = removeNode(dest);
    }

    polyNode* curNode = dest->next;
    polyNode* pastNode = dest;

    while(curNode != NULL)
    {
        while (curNode->val.coef == 0)
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

void calculateDerivate(polyNode* poly)
{
    while(poly != NULL)
    {
        poly->val.coef *= poly->val.degree;
        poly->val.degree--;

        poly = poly->next;
    }
}

polyNode* findNodeWithDegree(polyNode* poly, int degree)
{
    while(poly != NULL)
    {
        if(poly->val.degree == degree)
            return poly;

        poly = poly->next;
    }

    return poly;
}

int main()
{
    srand(time(NULL));

    monom initMonom = {0, 1};
    polyNode* poly1 = createNode(&initMonom);

    printf("Please, enter coef and degree of monomial\n");
    do 
    {
        monom tmp;

        printf("> ");
        if(!scanf("%d %d", &tmp.coef, &tmp.degree) || feof(stdin))
            break; 
        
        polyNode* sameDegree = findNodeWithDegree(poly1, tmp.degree);

        if(sameDegree != NULL)
            sameDegree->val.coef += tmp.coef;
        else
            appendNode(poly1, &tmp);
    }while(!feof(stdin));


    poly1 = clearFromZeroes(poly1);
    polyNode* poly2 = appendList(NULL, poly1);

    calculateDerivate(poly1);
    poly1 = clearFromZeroes(poly1);

    printPoly(poly1);
    printPoly(poly2);
}
