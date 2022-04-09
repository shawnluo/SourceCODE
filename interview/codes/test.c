#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

typedef struct Node
{
    int data;
    struct Node *next;
}node, *pNode;

#define SIZE sizeof(node)

void showme(pNode p)
{
    assert(p);
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

pNode fun(int *str, int len)
{
    pNode pHead, p1, p2;
    pHead = (pNode)malloc(SIZE);
    pHead->data = str[0];
    pHead->next = NULL;

    p1 = p2 = pHead;

    for(int i = 1; i < len; i++)
    {
        p1 = (pNode)malloc(SIZE);
        p1->data = str[i];
        p1->next = NULL;

        p2->next = p1;
        p2 = p1;
    }

    return pHead;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    pNode pHead = fun(arr, 5);
    
    showme(pHead);

    return 0;
}