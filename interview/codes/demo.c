#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct node
{
    int data;
    struct node *next;
}Node, *pNode;


typedef struct node_d
{
    int data;
    struct node_d *next;
    struct node_d *pre;
}Node_d, *pNode_d;



#define LEN sizeof(Node)
#define LEN_d sizeof(Node_d)

//1. 
pNode ll_create(int num[], int len)
{
    pNode pHead = NULL, p = NULL;
    int i;

    for(i = len - 1; i >= 0; i--)
    {
        p = (pNode)malloc(len);
        memset(p, 0, len);
        p->data = num[i];
        p->next = pHead;
        pHead = p;
    }

    return pHead;
}

//2.
pNode *ll_ins_front(pNode *ppHead, int target, int new_data)
{
    pNode *pp = ppHead;
    while(*pp && (*pp)->data != target)
    {
        pp = &(*pp)->next;
    }
    if(!*pp)
    {
        perror("cannot find it!");
        return ppHead;
    }

    pNode new = (pNode)malloc(LEN);
    new->data = new_data;
    new->next = *pp;
    *pp = new;

    return ppHead;
}

//3. 
int ll_ins_behind(pNode *ppHead, int target, int new_data)
{
    pNode *pp = ppHead;
    while(*pp && (*pp)->data != target)
    {
        pp = &(*pp)->next;
    }

    pNode new = (pNode)malloc(LEN);
    new->data = new_data;
    new->next = (*pp)->next;
    (*pp)->next = new;

    return 0;
}

//4. 
int ll_del(pNode *ppHead, int target)
{
    pNode *pp = ppHead;
    while(*pp && (*pp)->data != target)
    {
        pp = &((*pp)->next);
    }

    pNode tmp = *pp;
    *pp = (*pp)->next;
    free(tmp);

    return 0;
}

//5.
pNode ll_sort()
{
    return NULL;
}

//6. 
pNode ll_merge_sorted(pNode pHead1, pNode pHead2)
{
    pNode p1 = pHead1;
    pNode p2 = pHead2;

    // insert p2 to p1: 
    //  if p2 > p1, then insert behind
    //  if p2 < p1, then insert behind
    //for(p2 = pHead2; p2; p2 = p1->next)

    while(p2)
    {
        while(p1)
        //for(p = p1; p != NULL; p = p->next)
        {
            if(p2->data < p1->data)
            {
                ll_ins_front(&pHead1, p1->data, p2->data);
                p1 = p1->next;
                break;
            }
            
            if(p1->next == NULL)
            {
                ll_ins_behind(&pHead1, p1->data, p2->data);
                p1 = p1->next;
                break;
            }
            p1 = p1->next;
        }
        p2 = p2->next;
    }

    return pHead1;
}

//7.
pNode ll_locate_circle()
{
    return NULL;
}


//============= double ll
//8.
pNode_d lld_create(int *arr, int len)
{
    pNode_d pHead = NULL;
    int i;

    pHead = (pNode_d)malloc(LEN_d);
    pHead->pre = NULL;
    pHead->next = NULL;
    pHead->data = arr[0];
    pNode_d pTail = pHead;

    for(i = 1; i < len; i++)
    {
        pNode_d new = (pNode_d)malloc(LEN_d);
        new->data = arr[i];
        new->pre = pTail;
        new->next = NULL;
        pTail->next = new;
        pTail = new;
    }

    return pHead;
}

//9. 
pNode_d lld_ins()
{
    return NULL;
}

//10
pNode_d lld_del_front()
{
    return NULL;
}

//11
pNode_d lld_del_behind()
{
    return NULL;
}


void showme(pNode pHead)
{
    while(pHead)
    {
        printf("%d\t", pHead->data);
        pHead = pHead->next;
    }
    printf("\n");
}

void showme_d(pNode_d pHead)
{
    while(pHead)
    {
        printf("%d, ", pHead->data);
        pHead = pHead->next;
        //pNode_d tmp = pHead->pre;
        //printf("%d\t", tmp->data);
        //printf("ddd\t");
    }

    printf("\n");
}


int main(void)
{
    int data1[5] = {0, 1, 7, 9, 22};
    int data2[7] = {4, 6, 8, 20, 23, 100, 988};
    int len1 = sizeof(data1) / sizeof(data1[0]);
    int len2 = sizeof(data2) / sizeof(data2[0]);
    
    pNode pHead1 = ll_create(data1, len1);
    showme(pHead1);

    pNode pHead2 = ll_create(data2, len2);
    showme(pHead2);

    pNode newHead = ll_merge_sorted(pHead1, pHead2);
    showme(newHead);

    //ll_ins_behind(&pHead, 22, 198);
    //showme(pHead);

    //ll_del(&pHead, 9);
    //showme(pHead);

    //ll_del(&pHead, 0);
    //showme(pHead);


    //pNode *ppHead = ll_ins_front(&pHead, 1, 122);
    //showme(*ppHead);

    //pNode_d pHead_d = lld_create(data, len);
    //showme(pHead_d);

    //showme_d(pHead_d);

    return 0;
}