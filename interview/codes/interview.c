
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <math.h>
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


//#define D_01
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

//#define D_02
/******************** Strings ******************************
01. reverse
02. sub string
03. remove duplicate characters
04. replace all spaces with '%20'
05. anagrams or not
06. 
***************************************************************/

//#define D_03
/******************** Arrays ******************************
01. pointer array vs array pointer
02. multiple arrays
03. 
***************************************************************/

//#define D_04
/******************** others ******************************
01. rotate the image by 90 degrees, and do it in place

***************************************************************/


#if defined D_01

typedef struct Node
{
	int id;
	struct Node *next;
} NODE, *pNODE;

#define LEN sizeof(NODE)

pNODE Create_Linkedlist(int data[], int len)
{
	pNODE pHead = NULL, p = NULL;

	if(0 == len)
	{
		return NULL;
	}

	while(len--)
	{
		p = (pNODE)malloc(LEN);
		if(NULL == p)
		{
			perror("malloc failed!");
			exit(-1);
		}
		p->id = data[len];
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

void Del_Node(pNODE *ppHead, int target_id)
{
	assert(*ppHead);
	
	pNODE *pp = ppHead;

	while(*pp && (*pp)->id != target_id)	//find the node
	{
		pp = &(*pp)->next;
	}
	
	if(!*pp)
	{
		perror("Cannot find it");
		return;
	}

	//delete operations
	pNODE tmp = *pp;

	*pp = (*pp)->next;

	free(tmp);
	tmp = NULL;
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
	
	if(pHead->next == pHead)
	{
		return 1;
	}

	for(pCur = pHead; ; pCur = pCur->next)
	{
		if(NULL == pCur)
		{
			return 0;	//no
		}
		
		for(pFind = pHead; pFind != pCur; pFind = pFind->next)
		{
			if(pFind->next == pCur->next)
			{
				return 1;
			}
		}
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
	int data[][5] = {
						{1, 2, 3, 4, 5},
						{6, 7, 8, 9, 10},
						{11, 12, 13, 14, 15}};

	pNODE pHead = NULL;
	int len = sizeof(data[0]) / sizeof(data[0][0]);
	
	pHead = Create_Linkedlist(data[0], len);
	Showme(pHead);

	Insert_Node_Front(&pHead, 1, 300);
	Showme(pHead);

	Insert_Node_Behind(&pHead, 5, 500);
	Showme(pHead);

	Del_Node(&pHead, 300);
	Showme(pHead);
	
	Create_Circular(pHead, 3);
//	Showme(pHead);

	int x = Has_Circular(pHead);
	printf("x = %d\n", x);

	pNODE pHead2 = NULL;
	int len2 = sizeof(data[1]) / sizeof(data[1][0]);

	Sorting_Node(pHead);
	
	return 0;
}

#elif defined D_02

#elif defined D_0x

#define ENABLE_BIT 0x07
#define VOLUME_START_BIT 0x0
#define VOLUME_END_BIT 0x7

void Control_Sound(int Volume, bool Enable)
{
	int i = 0, data = 0;

	int volatile *reg = (int *)0x80000000;
	*reg |= 1 << 0x7;

	if(TRUE == Enable)
	{
		*reg |= (1 << );
	}
}

int main(int argc, char *argv[])
{
	
}

#else

#endif
