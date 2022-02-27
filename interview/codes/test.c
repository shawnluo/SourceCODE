
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
    //printf("print ll: ");
    while(p != NULL)
    {
        printf("%d ", p->i);
        p = p->next;
    }
    printf("\n");
}


int create_ll(pData *ppHead, int *arr, int len)
{
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

int del_node_byData(pData *ppHead, int target)
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

int reverse_ll(pData *ppHead)
{
    assert(*ppHead);

    pData p1, p2, pTmp;
    p1 = p2 = pTmp = *ppHead;
    /* using p to point to the current node, then 
    */

    if(p1->next == NULL)    // the ll only has one node which is head
    {
        return 0;
    }

    p1 = p1 ->next;
    pTmp = p1->next;
    p2->next = NULL;    // tail
    p1->next = p2;
    p2 = p1;
    *ppHead = p1;

    while(pTmp != NULL)
    {
        p1 = pTmp;
        pTmp = pTmp->next;
        p1->next = p2;
        p2 = p1;
        *ppHead = p1;
    }

    return 0;
}

// delete the node by the specified node address
// we do NOT have to use *ppHead. because we will not delete the head node.
int del_node_byAddress(pData *ppHead, pData pNode)
{
    assert(*ppHead);

    pData *pp = ppHead;

    while(*pp != NULL && (*pp) != pNode)
    {
        pp = &(*pp)->next;
    }

    if(*pp == NULL)
    {
        printf("can NOT find the node!\n");
        return 1;
    }

    pData pTmp;
    pTmp = *pp;

    *pp = pTmp->next;
    free(pTmp);

    return 0;
}

int remove_dup_ll(pData *ppHead)
{
    assert(*ppHead);

    pData p1, p2, pTmp;
    p1 = p2 = *ppHead;
    for(p1 = *ppHead; p1->next != NULL; p1 = p1->next)
    {
        //for(p2 = p1->next; p2 != NULL; p2 = p2->next)
        for(p2 = p1->next; p2 != NULL; p2 = p2->next)
        {
            if(p1->i == p2->i)
            {
                #if 1
                del_node_byAddress(ppHead, p2);
                //del_node_byData(ppHead, p2->i);
                //p2 = p1;
                #else
                pTmp->next = p2->next;

                free(p2);
                #endif
                p2 = pTmp;
            }
            else
            {
                pTmp = p2;
            }
        }
    }
}

// find the ll length, then traverse the ll
pData find_element_toLast_ll(pData *ppHead, int n)
{
    assert(*ppHead);

    int len_ll = 0;
    pData p = *ppHead;

    while(p != NULL)
    {
        len_ll++;
        p = p->next;
    }

    p = *ppHead;
    // nth to the end is len_ll - n;
    int x = len_ll - n;
    while(x-- != 0)
    {
        p = p->next;
    }

    printf("%d\n", p->i);
    return p;
}

// add new node to the ll tail
int add_tail(pData *ppHead, int newData)
{
    if(*ppHead == NULL)
    {
        *ppHead = (pData)malloc(LEN);
        (*ppHead)->i = newData;
        (*ppHead)->next = NULL;
        return 0;
    }

    pData p = *ppHead;
    pData pNew = NULL;
    while(p->next != NULL)
    {
        p = p->next;
    }
    pNew = (pData)malloc(LEN);
    pNew->i = newData;
    p->next = pNew;
    pNew->next = NULL;

    return 0;
}


// add 2 ll, each node contains a single digit. the digits are stored in reverse order.
pData add_ll(pData pHead1, pData pHead2)
{
    assert(pHead1 || pHead2);

    int inc = 0;

    int len1 = 0;
    int len2 = 0;

    pData p1 = pHead1;
    pData p2 = pHead2;

    while(p1 != NULL)
    {
        len1++;
        p1 = p1->next;
    }

    while(p2 != NULL)
    {
        len2++;
        p2 = p2->next;
    }

    printf("len1 = %d, len2 = %d\n", len1, len2);


#if 1
    // choose the longer one to travel, 
    // p1 5        p2 5
    //pData pHead_a = len1 >= len2 ? pHead1 : pHead2;     // 5 6      6
    //pData pHead_b = len2 <= len1 ? pHead2 : pHead1;     // 6 5      5

    pData pNew = NULL;
    int newData = 0;
    int i1, i2;

    while(p1->next != NULL || p2->next != NULL)
    {
        if(p1->next == NULL)    
            i1 = 0;
        else
        {
            i1 = p1->i;
            p1 = p1->next;
        }

        if(p2->next == NULL)    
            i2 = 0;
        else
        {
            i2 = p2->i;
            p2 = p2->next;
        }

        newData = i1 + i2 + inc;
        if (newData >= 10)
        {
            newData -= 10;
            inc = 1;
        }
        else
        {
            inc = 0;
        }

        add_tail(&pNew, newData);
    }

    if(inc == 1)
    {
        add_tail(&pNew, 1);
    }

    print_ll(pNew);
    free_ll(pNew);
#endif
    return NULL;
}

int main()
{
    int arr1[] = {1, 1, 1, 1, 1};
    int arr2[] = {1, 2, 3, 4, 5};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    pData pHead1 = NULL;
    pData pHead2 = NULL;

    int ret;
    ret = create_ll(&pHead1, arr1, len1);
    printf("ret = %d\n", ret);
    print_ll(pHead1);

    ret = create_ll(&pHead2, arr2, len2);
    printf("ret = %d\n", ret);
    print_ll(pHead2);

    add_ll(pHead1, pHead2);

    free_ll(pHead1);
    free_ll(pHead2);

    //del_node_byData(&pHead, 1);
    //print_ll(pHead);

    //del_node_byAddress(&pHead, pHead->next);
    //print_ll(pHead);

    //ins_node_front(&pHead, 100, 1);
    //print_ll(pHead);

    //ins_node_behind(&pHead, 1000, 1);
    //print_ll(pHead);

    //reverse_ll(&pHead);
    //print_ll(pHead);
    
    //remove_dup_ll(&pHead);
    //print_ll(pHead);

    //find_element_toLast_ll(&pHead, 5);

    //free_ll(pHead);

//-------------------
#if 0
    pData pNew = NULL;
    add_tail(&pNew, 888);
    add_tail(&pNew, 2222);
    add_tail(&pNew, 777);

    print_ll(pNew);
    free_ll(pNew);
#endif

    return 0;
}