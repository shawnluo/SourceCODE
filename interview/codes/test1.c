#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    creat linkedlist
*/

typedef struct data
{
    int i;
    struct data *next;
} Data, *pData;

#define SIZE_ll sizeof(struct data)

void showme(pData pHead)
{
    while(pHead)
    {
        printf("%d, ", pHead->i);
        pHead = pHead->next;
    }

    printf("\n");
}


pData create_ll(int *arr, int len)
{
    int i;
    pData p1, p2, pHead;   // p1 points to new created link

    if(len <= 0)    return NULL;
    if(arr == NULL) return NULL;

    // for the head of the linked list
    p1 = p2 = pHead = (pData)malloc(SIZE_ll);
    pHead->i = arr[0];
    pHead->next = NULL;

    for(i = 1; i < len; i++)
    {
        p1 = (pData)malloc(SIZE_ll);
        p1->i = arr[i];
        p1->next  = NULL;
        p2->next = p1;
        p2 = p1;
    }

    return pHead;
}

/*
pData create_ll_ext(int *arr, int len)
{
    pData p, pHead;     // p is used to malloc a new link node
    p = pHead = NULL;

    while(len-- > 0)
    {
        p = (pData)malloc(SIZE_ll);
        p->i = arr[len];
        p->next = pHead;
        pHead = p;
    }

    return pHead;
}
*/

pData Create_ll_ext(int *array, int len)
{
    pData pHead = NULL, p = NULL;
    int i = 0;

    for (i = len; i >= 0; i--)
    {
        p = (pData)malloc(SIZE_ll);
        memset(p, 0, SIZE_ll);
        p->i = *(array + i);
        p->next  = pHead;
        pHead     = p;
    }

    return pHead;
}


// insert a new node behind of node
// the ll head still keeps the memory address
/* target: the new node will be inserted behind of this node
    newData: the new node
*/
int Ins_behind_ll(pData *ppHead, int newData, int target)
{
    if(*ppHead == NULL)
    {
        printf("ll is invalid!\n");
        return -1;
    }

    pData *pp = ppHead;

    while(((*pp)->i != target) && (*pp != NULL))
    {
        pp = &(*pp)->next;
    }
    if(*pp == NULL)
    {
        printf("can not find the target\n");
        return -2;
    }

/*
    pData pTmp = p;
    p = (pData)malloc(SIZE_ll);
    p->i = newData;
    p->next = pTmp->next;
    pTmp->next = p;
*/
    return 0;
}


// insert a new node infront of the specific node
int Ins_infront_ll(pData *ppHead, int newData, int target)
{
    if(*ppHead == NULL)
    {
        printf("invalid ll\n");
        return -1;
    }

    pData *pp = ppHead;
    while(((*pp)->i != target) && (*pp != NULL))
    {
        //printf("%x\n", p);
        pp = &(*pp)->next;
    }
    if(*pp == NULL)
    {
        printf("can NOT find the target\n");
        return -2;
    }

    pData pTmp = *pp;
    

    return 0;
}


int main()
{
    int arr[] = {11, 12, 13, 14, 15};
    int num = sizeof(arr) / sizeof(arr[0]);
    int ret;
    pData pHead = Create_ll_ext(arr, num);
    showme(pHead);

    ret = Ins_behind_ll(&pHead, 33, 112);
    printf("ret = %d\n", ret);
    showme(pHead);

/*
    ret = Ins_infront_ll(pHead, 33, 111);
    printf("ret = %d\n", ret);
    showme(pHead);
*/
    return 0;
}