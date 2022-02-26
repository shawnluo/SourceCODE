
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
    printf("print ll!\n");
    while(p != NULL)
    {
        printf("p->i = %d\n", p->i);
        p = p->next;
    }
}

pData create_ll()
//void create_ll(pData *ppHead)
{
    pData pHead = NULL;//*ppHead;
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    pData p = NULL;

    while(len > 0)
    {
        p = (pData)malloc(LEN);
        memset(p, 0, LEN);
        p->i = arr[len - 1];
        p->next = pHead;
        pHead = p;
        len--;
    }
    //print_ll(pHead);
    return pHead;
}

int main()
{
    pData pHead = NULL;
    pHead = create_ll();
    //create_ll(&pHead);
    //printf("ret = %d\n", ret);
    print_ll(pHead);

    free_ll(pHead);
    return 0;
}