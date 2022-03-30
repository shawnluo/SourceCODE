#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


typedef struct Node
{
    int idx;
    struct Node *next;
}node, *pNode;

#define SIZE sizeof(node)

void showme(pNode pHead)
{
    while(pHead)
    {
        printf("%d ", pHead->idx);
        pHead = pHead->next;
    }
    printf("\n");
}



pNode create_ll(int arr[], int n)
{
    pNode pHead = NULL;
    pNode p = NULL;

    while(n--)
    {
        p = (pNode)malloc(SIZE);
        p->idx = arr[n];
        p->next = pHead;
        pHead = p;
    }

    return pHead;
}

int del_node(pNode *ppHead, int num)
{
    assert(*ppHead);
    pNode *pp = ppHead;

    while(*pp && (*pp)->idx != num)
    {
        pp = &(*pp)->next;
    }
    if(!*pp)
    {
        return -1;   //can not find the node
    }

    pNode tmp = *pp;
    *pp = (*pp)->next;
    free(tmp);

    return 0;
}

int insert_node_infront(pNode *ppHead, int num, int newNum)
{
    assert(*ppHead);
    pNode *pp = ppHead;

    while(*pp && (*pp)->idx != num)
    {
        pp = &(*pp)->next;
    }
    if(!*pp)
        return -1;

    pNode p = (pNode)malloc(SIZE);
    p->idx = newNum;

    //pNode tmp = *pp;
    p->next = *pp;
    *pp = p;

    return 0;
}

int insert_node_after(pNode *ppHead, int num, int newNum)
{
    assert(*ppHead);
    pNode *pp = ppHead;

    while(*pp && (*pp)->idx != num)
    {
        pp = &(*pp)->next;
    }
    if(!*pp)
        return -1;

    pNode p = (pNode)malloc(SIZE);
    p->idx = newNum;

    p->next = (*pp)->next;
    (*pp)->next = p;

    return 0;
}

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    pNode pHead = create_ll(arr, 5);
    showme(pHead);

    //del_node(&pHead, 4);
    //showme(pHead);

    //insert_node_infront(&pHead, 1, 100);
    //showme(pHead);

    insert_node_after(&pHead, 5, 50);
    showme(pHead);

    return 0;
}