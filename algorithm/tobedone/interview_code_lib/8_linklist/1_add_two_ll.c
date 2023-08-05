#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
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

typedef struct NODE {
    int data;
    struct NODE *next;
}node, *pNode;

#define LEN sizeof(node)

void showme(pNode pHead) {
    while(pHead) {
        printf("%d, ", pHead->data);
        pHead = pHead->next;
    }
    printf("\n");
}

pNode creat_ll(int *arr, int size) {
    assert(arr);
    pNode pHead = NULL;
    pNode p = NULL;

    while(size--) {
        pHead = (pNode)malloc(LEN);
        pHead->data = arr[size];
        pHead->next = p;
        p = pHead;
    }

    return pHead;
}

pNode creat_ll2(int *arr, int size) {
    assert(arr);
    pNode pHead = NULL;
    pNode pNew = NULL;
    pNode pTmp = NULL;

    pNew = (pNode)malloc(LEN);
    pNew->data = arr[0];
    pNew->next = NULL;

    pHead = pNew;
    pTmp = pNew;

    if(size <= 1) {
        return pHead;
    }

    for(int i = 1; i < size; i++) {
        pNew = (pNode)malloc(LEN);
        pNew->data = arr[i];
        pTmp->next = pNew;
        pTmp = pNew;
    }

    return pHead;
}

int reverse_ll(pNode *ppHead) {
    pNode *pp = ppHead;
    pNode p_prev = NULL;
    pNode p_next = NULL;

    while(*pp) {
        p_next = (*pp)->next;
        (*pp)->next = p_prev;
        p_prev = *pp;
        *pp = p_next;
    }
    *ppHead = p_prev;

    return 0;
}


int add_newNode(pNode *ppHead, int data) {
    if(!(*ppHead)) {
        *ppHead = (pNode)malloc(LEN);
        (*ppHead)->data = data;
        (*ppHead)->next = NULL;

        return 0;
    }

    pNode *pp = ppHead;
    while(*pp) {
        pp = &(*pp)->next;
    }
    pNode pNew = (pNode)malloc(LEN);
    pNew->data = data;
    pNew->next = NULL;
    *pp = pNew;

    return 0;
}


//travel l1 || l2
pNode add_ll(pNode pHead1, pNode pHead2) {
    pNode l1 = pHead1, l2 = pHead2;
    int add = 0;
    while(l1 && l2) {
        l1->data = l1->data + l2->data + add;
        if(l1->data >= 10) {
            l1->data -= 10;
            add = 1;
        } else {
            add = 0;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    while(l1) {
        l1->data = l1->data + add;
        if(l1->data >= 10) {
            l1->data -= 10;
            add = 1;
        } else {
            add = 0;
        }
        l1 = l1->next;
    }

    while(l2) {
        int tmp = l2->data + add;
        if(tmp >= 10) {
            tmp -= 10;
            add = 1;
        } else {
            add = 0;
        }
        add_newNode(&pHead1, tmp);
        l2 = l2->next;
    }

    if(add == 1) {
        add_newNode(&pHead1, 1);
    }

    return pHead1;
}


int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int arr2[] = {8, 9, 6, 0, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    pNode pHead1 = creat_ll2(arr, size);
    showme(pHead1);

    pNode pHead2 = creat_ll2(arr2, size2);
    showme(pHead2);

    //pNode pHead3 = NULL;
    //add_newNode(&pHead3, 999);

    pNode pHead = add_ll(pHead1, pHead2);
    showme(pHead);

	return 0;
}