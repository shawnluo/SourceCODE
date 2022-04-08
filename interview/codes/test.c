#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

typedef struct Node{
    int num;                //4 bytes
    struct Node *next;      //8 bytes

} node, *pNode;

#define SIZE sizeof(node)

void showme(pNode pHead)
{
    assert(pHead);

    while(pHead)
    {
        printf("%d ", pHead->num);
        pHead = pHead->next;
    }
    printf("\n");
}

pNode create_linkedlist(int *arr, int len)
{
    pNode pHead = NULL;
    pNode p = NULL;

    while(len--)
    {
        p = (pNode)malloc(SIZE);
        p->num = arr[len];
        p->next = pHead;
        pHead = p;
    }

    return pHead;
}

pNode reverse_ll(pNode pHead)
{
    assert(pHead);

    pNode cur = pHead;
    pNode pre = NULL;

    while(cur)
    {
        pNode tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

pNode add_node(pNode pHead, int data)
{
    if(!pHead)
    {
        pHead = (pNode)malloc(SIZE);
        pHead->num = data;
        pHead->next = NULL;
        return pHead;
    }

    pNode p = pHead;
    while(p->next)
    {
        p = p->next;
    }
    pNode newNode = (pNode)malloc(SIZE);
    newNode->num = data;
    newNode->next = NULL;
    p->next = newNode;

    return pHead;
}



int main(void)
{
    int arr1[] = {2, 4, 14, 71, 125};
    //int arr2[] = {1, 2, 3, 4, 5, 9};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    //int len2 = sizeof(arr2) / sizeof(arr2[0]);

    pNode pHead1 = create_linkedlist(arr1, len1);
    showme(pHead1);

    pHead1 = reverse_ll(pHead1);
    showme(pHead1);

    pNode pHead = NULL;
    pHead = add_node(pHead, 1000);
    showme(pHead);
    pHead = add_node(pHead, 2000);
    showme(pHead);

    return 0;
}