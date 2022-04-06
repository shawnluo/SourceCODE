#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

typedef struct data{
    int num;                //4 bytes
//    int x;                  //4 bytes
    struct data *next;      //8 bytes

} data, *pData;

#define SIZE sizeof(data)

void showme(pData head)
{
    if(!head)
    {
        printf("empty!\n");
        return;
    }
    assert(head);
    while(head)
    {
        printf("%d ", head->num);
        head = head->next;
    }
    printf("\n");
}

pData create_linkedlist(int *arr, int size)
{
    pData head = NULL, p = NULL;
    while(size--)
    {
        p = (pData)malloc(SIZE);
        p->num = arr[size];
        p->next = head;
        head = p;
    }

    return head;
}

int insert_ll_infront(pData *ppHead, int target, int newData)
{
    assert(*ppHead);

    pData *pp = ppHead;
    while(*pp && (*pp)->num != target)
    {
        pp = &(*pp)->next;
    }
    if(*pp == NULL)
    {
        printf("can not find it\n");
        return -1;
    }
    pData newNode = (pData)malloc(SIZE);
    newNode->num = newData;
    newNode->next = *pp;
    *pp = newNode;

    return 0;
}

int insert_ll_after(pData pHead, int target, int newData)
{
    if(!pHead)
    {
        printf("Empty!\n");
        return -1;
    }
    assert(pHead);
    pData p = pHead;
    while(p && p->num != target)
    {
        p = p->next;
    }

    if(!p)
    {
        printf("can not find it\n");
        return -1;
    }
    pData tmp = (pData)malloc(SIZE);
    tmp->num = newData;
    tmp->next = p->next;
    p->next = tmp;

    return 0;
}

int del_ll_node(pData *ppHead, int target)
{
    assert(*ppHead);
    pData *pp = ppHead;
    while(*pp && (*pp)->num != target)
    {
        pp = &(*pp)->next;
    }

    if(!*pp)
    {
        printf("can not find it\n");
        return -1;
    }
    pData tmp = *pp;
    *pp = (*pp)->next;
    free(tmp);

    return 0;
}

int del_ll_all(pData pHead)
{
    assert(pHead);
    pData p = pHead;

    while(pHead)
    {
        p = pHead;
        pHead = pHead->next;
        free(p);
    }

    //*ppHead = NULL;
    return 0;
}

int add_newNode_ll(pData *ppHead, int newData)
{
    pData p = NULL;
    if(!*ppHead)
    {
        *ppHead = (pData)malloc(SIZE);
        (*ppHead)->num = newData;
        (*ppHead)->next = NULL;
        return 0;
    }

    p = *ppHead;
    while(p->next != NULL)
    {
        p = p->next;
    }
    pData newNode = NULL;
    newNode = (pData)malloc(SIZE);
    newNode->num = newData;
    newNode->next = NULL;
    p->next = newNode;

    return 0;
}

/*
    linked list addation
*/
pData add_2_ll(pData pHead1, pData pHead2)
{
    int inc = 0, newData = 0;
    pData p1 = pHead1, p2 = pHead2, pHead3 = NULL;
    for(p1 = pHead1, p2 = pHead2; p1 != NULL || p2 != NULL;)
    {
        if(!p1)
        {
            //p1->num = 0;
            newData = (p2->num) + inc;
        }
        else if(!p2)
        {
            newData = (p1->num) + inc;
            //p2->num = 0;
        }
        else
        {
            newData = (p1->num) + (p2->num) + inc;
        }
        //printf("%d, ", newData);
        if(newData >= 10)
        {
            newData = newData - 10;
            inc = 1;
        }
        else
        {
            newData = newData;
            inc = 0;
        }

        add_newNode_ll(&pHead3, newData);

        if(!p1)
        {
            p2 = p2->next;
        }
        else if(!p2)
        {
            p1 = p1->next;
        }
        else
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    if(inc == 1)
    {
        add_newNode_ll(&pHead3, inc);
    }
    showme(pHead3);
    return pHead3;
}

int merge_ll(pData head1, pData head2)
{
    pData p1 = NULL;
    pData p2 = NULL;
    pData p3 = NULL;

    for(p1 = head1, p2 = head2; p1 != NULL || p2 != NULL;)
    {
        if(p1 == NULL)
        {
            add_newNode_ll(&p3, p2->num);
            p2 = p2->next;
            continue;
        }
        else if(p2 == NULL)
        {
            add_newNode_ll(&p3, p1->num);
            p1 = p1->next;
            continue;
        }

        if(p1->num <= p2->num)
        {
            add_newNode_ll(&p3, p1->num);
            p1 = p1->next;
        }
        else
        {
            add_newNode_ll(&p3, p2->num);
            p2 = p2->next;
        }
    }
    showme(p3);

    return 0;
}


int create_circular_ll(pData *ppHead)
{
    pData p = *ppHead;
    while(p->next)
    {
        p = p->next;
    }

    p->next = (*ppHead)->next->next;

    return 0;
}


int find_circular_entry_ll(pData pHead)
{
    pData p1 = pHead;
    pData p2 = pHead;
    //if(p1->next == p1)
    //{
    //    return p1->num;
    //}

    while(p2->next != NULL)
    {
        p1 = p1->next;
        p2 = p2->next->next;
        if(p1 == p2)
        {
            break;
        }
    }
    if(p2->next == NULL)
    {
        printf("no circular!\n");
        return -1;
    }

    p1 = pHead;
    while(p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1->num;
}


pData reverse(pData pHead)
{
    pData pre = NULL;
    pData cur = pHead;

    while(cur)
    {
        pData tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}


int main(void)
{
    int arr1[] = {2, 4, 14, 71, 125};
    int arr2[] = {1, 2, 3, 4, 5, 9};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    pData pHead1 = create_linkedlist(arr1, len1);
    showme(pHead1);
    //pData pHead2 = create_linkedlist(arr2, len2);
    //showme(pHead2);

    pData p = reverse(pHead1);
    showme(p);

    int ret;

    //ret = insert_ll_infront(&head, 130, 1000);
    //showme(head);

    //ret = insert_ll_after(head, 500, 2000);
    //showme(head);

    //ret = del_ll_node(&head, 500);
    //showme(head);

    //ret = del_ll_all(head);
    //showme(head);

    //pData head3 = NULL; 
    //add_newNode_ll(&head3, 1234);
    //showme(head3);

    //add_newNode_ll(&head3, 5678);
    //showme(head3);

    //pData pHead3 = add_ll(head1, head2);
    //showme(pHead3);

    //merge_ll(head1, head2);

    create_circular_ll(&pHead1);
    //showme(pHead1);

    ret = find_circular_entry_ll(pHead1);
    printf("%d\n", ret);

    return 0;
}