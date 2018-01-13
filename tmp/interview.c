

//https://codefights.com/interview-practice/task/pMvymcahZ8dY4g75q

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
//#include <iostream>
//#include <iomanip>

//#include "color.h"


/*************************
*		wrong cases
*************************/
//#define w_01	//wrong case NO.01		strcpy before malloc
//#define w_02	//wrong case NO.02		strncpy pointer cross-border
//#define w_03	//wrong case NO.03		try to get the length of a interger pointer array.
//#define w_05	//trying to change the data which were stored in RO data segment.
//#define w_06	//sizeof cannot be used in calculating dynamic array size. But it can used in
//calculating static array size

//#define D_01
/******************** LinkedList ******************************
 * 1. Basic operations on single linked list
 *      1.1 Create a single linked list
 *      1.2 Traverse a single linked list
 *      1.3 Find a node in a single linked list
 *      1.4 Insert a new node in a given single linked list
 *      1.5 Delete a node in a given single linked list
 * 2. Doubly linked list
 *      2.1 Create a doubly linked list
 *      2.2 Insert a new node in a given doubly linked list
 *      2.3 Delete a node in a given doubly linked list
 ***************************************************************/

//#define D_02
/******************** Strings ******************************
 * 01. reverse
 * 02. sub string
 * 03. remove duplicate characters
 * 04. replace all spaces with '%20'
 * 05. anagrams or not
 * 06. lowCase -> upperCase
 * 07. longest common substring of 2 strings
 * 08. longest_unrepeat_substring
 ***************************************************************/

//#define D_03
/******************** Arrays ******************************
 * 01. pointer array vs array pointer
 * 02. multiple arrays
 * 03.
 ***************************************************************/

//#define D_04
/******************** Recursion ******************************
 * 01. Power
 * 02.
 * 03.
 ***************************************************************/

//#define D_10
/******************** others ******************************
 * 01. rotate the image by 90 degrees, and do it in place
 *
 ***************************************************************/
#define test


#if defined test

typedef struct node
{
	int id;
	struct node *next;
} Node, *pNode;

#define LEN sizeof(Node)

pNode Create_LinkedList(int data[], int num)
{
	pNode pHead = NULL;
	pNode p = NULL;

	while(num-- > 0)
	{
		p = (pNode)malloc(LEN);
		p->id = data[num];
		p->next = pHead;
		pHead = p;
	}

	return pHead;
}

void Insert_Node_Front(pNode *ppHead, int target, int newId)
{
	assert(*ppHead);
	
	pNode *pp = ppHead;

	while(*pp && (*pp)->id != target)
	{
		pp = &(*pp)->next;
	}

	pNode newNode = (pNode)malloc(LEN);
	newNode->id = newId;
	newNode->next = *pp;

	*pp = newNode;
}

void Insert_Node_Behind(pNode pHead, int target, int newId)
{
	assert(pHead);

	pNode p = pHead;

	while(p && p->id != target)
	{
		p = p->next;
	}

	pNode newNode = (pNode)malloc(LEN);
	newNode->id = newId;
	newNode->next = p->next;

	p->next = newNode;
}

void Del_Node(pNode *ppHead, int target)
{
	assert(*ppHead);

	pNode *pp = ppHead;

	while(*ppHead && (*ppHead)->id != target)
	{
		pp = &(*pp)->next;
	}

	pNode tmp = NULL;
	tmp = *pp;

	*pp = (*pp)->next;

	tmp = NULL;
	free(tmp);
}

void showme(pNode pHead)
{
	assert(pHead);

	while(pHead)
	{
		printf("%d\t", pHead->id);
		pHead = pHead->next;
	}
	printf("\n");
}

int main(void)
{
	int data[3][5] = {
						{1, 2, 3, 4, 5},
						{6, 7, 8, 9, 10},
						{11, 12, 13, 14, 15}
					};

	pNode pHead = NULL;

	pHead = Create_LinkedList(data[0], 5);
	showme(pHead);

//	Insert_Node_Front(&pHead, 1, 300);
//	showme(pHead);

//	Insert_Node_Behind(pHead, 2, 500);
//	showme(pHead);

	Del_Node(&pHead, 2);
	showme(pHead);

	return 0;
}



#else

#endif
