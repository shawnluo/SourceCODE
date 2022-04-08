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

typedef struct Node
{
	int data;
	struct Node *next;
	struct Node *prev;
} node, *pNode;

#define SIZE sizeof(node)

void showme(pNode pHead)
{
	assert(pHead);
	while(pHead)
	{
		printf("%d ", pHead->data);
		pHead = pHead->next;
	}
	printf("\n");
}

pNode create_ll(int *arr, int len)
{
	assert(arr);
	
	pNode pHead = NULL;
	pNode p, pPre, pCur;

	pHead = (pNode)malloc(SIZE);
	pHead->data = arr[0];
	pHead->next = NULL;
	pHead->prev = NULL;
	pPre = pHead;

	if(len < 2)	return pHead;

	for(int i = 1; i < len; i++)
	{
		pCur = (pNode)malloc(SIZE);
		pCur->data = arr[i];
		pCur->next = NULL;

		pPre->next = pCur;
		
		pCur->prev = pPre;
		pPre = pCur;
		pCur = pCur->next;
	}
	return pHead;
}

pNode

int main(void)
{
	int arr[] = {1, 2, 3, 4, 5};
	int len = sizeof(arr) / sizeof(arr[0]);

	pNode pHead = create_ll(arr, len);
	showme(pHead);

	
	return 0;
}