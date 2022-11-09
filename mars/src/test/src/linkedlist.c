#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int num;
    struct data *next;
} DATA, *pData;

#define SIZE sizeof(struct data)


void showme(pData p) {
    if(!p) {
        return;
    }

    while(p) {
        printf("%d, ", p->num);
        p = p->next;
    }
    printf("\n");
}

//1. create
pData create_linkedlist(int *arr, int len) {
    pData pHead = NULL;
    pData p1 = NULL;
    pData p2 = NULL;
    pHead = (pData)malloc(SIZE);
    pHead->num = arr[0];
    pHead->next = NULL;
    p1 = pHead;
    p2 = pHead;

    for(int i = 1; i < len; i++) {
        p1 = (pData)malloc(SIZE);
        p1->num = arr[i];
        p1->next = NULL;
        p2->next = p1;
        p2 = p1;
    }

    return pHead;
}

pData create_linkedlist_ext(int *arr, int len) {
    pData pHead = NULL;
    pData p = NULL;
    while(len-- > 0) {
        p = (pData)malloc(SIZE);
        p->num = arr[len];
        p->next = pHead;
        pHead = p;
    }

    return pHead;
}



int main(void) {
    int arr[5] = {12, 4, 98, 3, 2};
    
    pData pHead = create_linkedlist_ext(arr, 5);
    showme(pHead);

    return 0;
}

//2. insert
//3. delete
//4. append
//5. reverse
//6. create loop
//7. loop entry
//8. linked list add another linked list, with carry bit