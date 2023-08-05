#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


typedef struct Data
{
    int id;
    struct Data *next;
}data, *pData;

#define size_ll sizeof(data)

void showme(pData pHead)
{
    while(pHead != NULL)
    {
        printf("%d ", pHead->id);
        pHead = pHead->next;
    }
    printf("\n");
}

pData create_ll(int *arr, int size)
{
    pData p = NULL;
    pData pHead = NULL;

    while(--size >= 0)
    {
        p = (pData)malloc(size_ll);
        p->id = arr[size];
        p->next = pHead;
        pHead = p;
    }
    return pHead;
}

pData append_ll(pData pHead, int data)
{
    pData p, tmp;
    if(pHead == NULL)
    {
        pHead = (pData)malloc(size_ll);
        pHead->id = data;
        pHead->next = NULL;
    }
    else
    {
        p = pHead;
        while(p->next != NULL)
        {
            p = p->next;
        }
        tmp = (pData)malloc(size_ll);
        tmp->id = data;
        tmp->next = NULL;
        p->next = tmp;
    }

    return pHead;
}


int del_ll(pData *ppHead, pData target)
{
    assert(*ppHead);

    pData *pp = ppHead;
    
    while(*pp && *pp != target)
    {
        pp = &(*pp)->next;
    }

    if(*pp == NULL)
    {
        printf("can not find it!\n");
        return 1;
    }

    pData tmp = *pp;
    *pp = (*pp)->next;
    free(tmp);

    return 0;
}


/*loop1 to go through the whole ll i[0 ~ N]
    loop2 to go through the j[i + 1, N]
        if arr[i] == arr[j], delete arr[j]
*/
pData rm_dup(pData pHead)
{
    assert(pHead);
    pData p1, p2;

    for(p1 = pHead; p1 != NULL; p1 = p1->next)
    {
        for(p2 = p1->next; p2 != NULL;)
        {
            if(p1->id == p2->id)
            {
                del_ll(&pHead, p2);
                //printf("p2: %d\n", p2->id);
                //p2 = p2->next;
            }
            else
            {
                p2 = p2->next;
            }
        }
    }

    return pHead;
}



int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    pData pHead = create_ll(arr, 5);
    //showme(pHead);
    //pHead = NULL;

    pHead = append_ll(pHead, 199);
    //showme(pHead);

    pHead = append_ll(pHead, 233);
    //showme(pHead);

    pHead = append_ll(pHead, 3);
    showme(pHead);

    //del_ll(&pHead, pHead->next);
    //showme(pHead);

    pHead = rm_dup(pHead);
    showme(pHead);

    return 0;
}