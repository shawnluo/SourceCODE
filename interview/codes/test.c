
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

typedef struct data
{
    int i;
    struct data *next;
}Data, *pData;

#define LEN sizeof(Data)

int free_ll(pData p)
{
    pData pTmp = NULL;
    while(p != NULL)
    {
        pTmp = p->next;
        free(p);
        p = pTmp;
    }

    return 0;
}

void print_ll(pData p)
{
    printf("print ll: ");
    while(p != NULL)
    {
        printf("%d ", p->i);
        p = p->next;
    }
    printf("\n");
}


int create_ll(pData *ppHead)
{
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    pData p = NULL;

    while(len > 0)
    {
        p = (pData)malloc(LEN);
        if(!p)
        {
            printf("malloc failed!\n");
            return -1;
        }
        memset(p, 0, LEN);
        p->i = arr[len - 1];
        p->next = *ppHead;
        *ppHead = p;
        len--;
    }

    return 0;
}

int del_node(pData *ppHead, int target)
{
    if(*ppHead == NULL)
    {
        printf("p is empty!\n");
        return -1;
    }
    pData *pp = ppHead;
    
    while(*pp != NULL && (*pp)->i != target)
    {
        pp = &((*pp)->next);
    }

    if(*pp == NULL)
    {
        printf("can NOT find the node!\n");
        return 1;
    }

    pData pTmp = *pp;
    *pp = (*pp)->next;
    free(pTmp);

    return 0;
}

int ins_node_front(pData *ppHead, int newData, int target)
{
    if(*ppHead == NULL)
    {
        printf("ll is empty!\n");
        return -1;
    }

    pData *pp = ppHead;
    while((*pp) != NULL && (*pp)->i != target)
    {
        pp = &((*pp)->next);
    }

    if(*pp == NULL)
    {
        printf("can NOT find the target!\n");
        return 1;
    }

    pData newNode = (pData)malloc(LEN);
    memset(newNode, 0, LEN);

    newNode->i = newData;
    newNode->next = *pp;
    *pp = newNode;

    return 0;    
}

int ins_node_behind(pData *ppHead, int newData, int target)
{
    if(*ppHead == NULL)
    {
        printf("ll is empty!\n");
        return -1;
    }

    pData p = *ppHead;
    while(p != NULL && p->i != target)
    {
        p = p->next;
    }
    pData newNode = (pData)malloc(LEN);
    newNode->i = newData;
    newNode->next = p->next;
    p->next = newNode;

    return 0;
}

int reverse_ll(pData pHead)
{
    assert(pHead);

    pData p = pHead;
}

int main()
{
    pData pHead = NULL;

    int ret = create_ll(&pHead);
    //printf("ret = %d\n", ret);
    print_ll(pHead);

    //del_node(&pHead, 1);
    //print_ll(pHead);

    ins_node_front(&pHead, 100, 1);
    print_ll(pHead);

    ins_node_behind(&pHead, 1000, 1);
    print_ll(pHead);

    free_ll(pHead);
    return 0;
}