#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>

typedef struct NODE{
    int num;
    struct NODE *next;
}node, *pNode;

#define SIZE sizeof(node)


void print_LL(pNode pHead)
{
    while(pHead)
    {
        printf("%d ", pHead->num);
        pHead = pHead->next;
    }
}


pNode create_LL(int *arr, int len)
{
    pNode pHead;
    pNode p;
    pHead = (pNode)malloc(SIZE);
    if(!pHead)  return NULL;
    pHead->num = arr[0];
    pHead->next = NULL;
    pNode p1 = pHead;
    pNode p2 = pHead;

    for(int i = 1; i < len; i++)
    {
        p1 = (pNode)malloc(SIZE);
        if(!p1)  return NULL;
        p1->num = arr[i];
        p2->next = p1;
        p2 = p1;
    }

    return pHead;
}


int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);

    pNode pHead = create_LL(arr, len);
    print_LL(pHead);

    return 0;
}