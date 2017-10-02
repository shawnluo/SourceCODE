
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "math.h"
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>
#include <stdbool.h>
//#include "color.h"


/*************************
*		wrong cases
*************************/
//#define w_01	//wrong case NO.01		strcpy before malloc
//#define w_02	//wrong case NO.02		strncpy pointer cross-border
//#define w_03	//wrong case NO.03		try to get the length of a interger pointer array.
//#define w_05	//trying to change the data which were stored in RO data segment.


#define D_01
/******************** LinkedList ******************************
1. Basic operations on single linked list
	1.1 Create a single linked list
	1.2 Traverse a single linked list
	1.3 Find a node in a single linked list
	1.4 Insert a new node in a given single linked list
	1.5 Delete a node in a given single linked list
2. Doubly linked list
	2.1 Create a doubly linked list
	2.2 Insert a new node in a given doubly linked list
	2.3 Delete a node in a given doubly linked list
***************************************************************/


#if defined D_01

typedef struct Node
{
	int id;
	struct Node *next;
} NODE, *pNODE;

#define LEN sizeof(NODE)

pNODE Create_Linkedlist(int liv_Data[], int len)
{
	pNODE pHead = NULL, p = NULL;

	while(len--)
	{
		p = (pNODE)malloc(LEN);
		if(NULL == p)
		{
			perror("malloc failed!");
			exit(-1);
		}
		p->id = liv_Data[len];
		p->next = pHead;
		pHead = p;
	}
	
	return pHead;
}

void Insert_Node_Front(pNODE *ppHead, int target_id, int new_id)
{
	assert(*ppHead);
	
	pNODE *pp = ppHead;

	while(*pp && (*pp)->id != target_id)
	{
		pp = &(*pp)->next;
	}

	if(NULL == *pp)
	{
		printf("Cannot find the node\n");
		return;
	}

	pNODE new_node = (pNODE)malloc(LEN);

	new_node->next = *pp;
	new_node->id = new_id;
	*pp = new_node;
}

void Insert_Node_Behind(pNODE *ppHead,int target_id,int new_id)
{
	assert(*ppHead);
	
	pNODE *pp = ppHead;

	while(*pp && (*pp)->id != target_id)
	{
		pp = &(*pp)->next;
	}

	if(NULL == *pp)
	{
		printf("Cannot find the node\n");
		return;
	}

	pNODE new_node = (pNODE)malloc(LEN);

	new_node->next = (*pp)->next;
	new_node->id = new_id;
	(*pp)->next = new_node;
}

void Create_Circular(pNODE pHead, int target_id)
{
	assert(pHead);
	
	pNODE p = pHead;

	while(p && p->id != target_id)
	{
		p = p->next;
	}

	pNODE pEnd = p;

	while(pEnd->next)
	{
		pEnd = pEnd->next;
	}

	pEnd->next = p;
}

int Has_Circular(pNODE pHead)
{
	assert(pHead);
	
	pNODE pCur = NULL, pFind = NULL;

	for(pCur = pHead; ; pCur = pCur->next)
	{
		if(NULL == pCur)
		{
			return 0;	//no
		}
		
		for(pFind = pHead; pFind != pCur; pFind = pFind->next)
		{
			
		}
	}
}

void test(void)
{
	int i = -1;

	while(--i)
	{
		printf("xxxxx\n");
	}
}

void Showme(pNODE pHead)
{
	while(pHead)
	{
		printf("%d\t", pHead->id);
		pHead = pHead->next;
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	int liv_Data[][5] = {
						{1, 2, 3, 4, 5},
						{6, 7, 8, 9, 10},
						{11, 12, 13, 14, 15}};

	pNODE pHead = NULL;
	int len = sizeof(liv_Data[0]) / sizeof(liv_Data[0][0]);
	
	pHead = Create_Linkedlist(liv_Data[0], len);
	Showme(pHead);

	Insert_Node_Front(&pHead, 1, 300);
	Showme(pHead);

	Insert_Node_Behind(&pHead, 5, 500);
	Showme(pHead);

	Create_Circular(pHead, 3);
//	Showme(pHead);

//	Has_Circular(pHead);
	test();
	return 0;
}

#else

#endif
