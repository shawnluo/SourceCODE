//http://blog.csdn.net/vanpire110/article/details/7931086


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

void rotate(int mat[][5], int n)
{
    int i = 0, j = 0, tmp;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            tmp       = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = tmp;
        }
    }
}

void showme(int mat[][5], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

//void tt(int )

int main(void)
{
//    int n = 5, i, j;
	int n = 5;
    int mat[5][5] = { {  1,  2,  3,  4,  5 },
                      {  6,  7,  8,  9, 10 },
                      { 11, 12, 13, 14, 15 },
                      { 16, 17, 18, 19, 20 },
                      { 21, 22, 23, 24, 25 } };

    showme(mat, n);
    printf("\n");

#if 0
    int **p = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++)
    {
        *(p + i) = (int *)malloc(sizeof(int) * n);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            *(*(p + i) + j) = mat[i][j];
            printf("%d\t", *(*(p + i) + j));
        }
        printf("\n");
    }

//	printf();
#endif
    printf("sizeof(mat) is: %d\n", (int)sizeof(mat));


    rotate(mat, n);
	showme(mat, n);
}

#elif defined test2
void swap(int *x, int *y)
{
	int tmp = 0;
	
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void sorting_bubble(int arr[], int num)
{
	printf("num = %d\n", num);

	int i, j;

	for(i = 0; i < num - 1; i++)
	{
		for(j = i + 1; j < num; j++)
		{
			if(arr[i] > arr[j])
			{
				swap(&arr[i], &arr[j]);
			}
		}
	}
}

void sorting_quick(int arr[], int start, int end)
{
	int left, right;

	if(start < end)
	{
		left = start + 1;
		right = end;

		while(left <= right)
		{
			while(arr[left] <= arr[start])
			{
				left++;
			}

			while(arr[right] > arr[start])
			{
				right--;
			}

			if(left < right)
			{
				swap(&arr[left], &arr[right]);
			}
		}
		swap(&arr[start], &arr[right]);

		sorting_quick(arr, start, right - 1);
		sorting_quick(arr, right + 1, end);		
	}
}

int main(void)
{
	int arr[5] = {7, 32, 9, 111, 76};
	
//	sorting_bubble(arr, sizeof(arr) / sizeof(arr[0]));
	sorting_quick(arr, 0, 4);

	for(int i = 0; i < 5; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
	
	return 0;
}

#elif defined Power
int Power(int i, int j)
{
	int ret = 0;
	
	if(0 == j)
	{
		return 1;
	}

	if(1 == j)
	{
		return i;
	}

	if((j % 2) == 0)
	{
		ret = Power(i, j / 2) * Power(i, j / 2);
	}
	else
	{
		ret = Power(i, j / 2) * Power(i, j / 2) * i;
	}

	return ret;
}

int main(void)
{
	int ret = Power(3, 3);
	printf("ret = %d\n", ret);
	
	return 0;
}

#elif defined String_Demo
void Reverse_String(char *s)
{
	assert(s);

	char *start = s;
	char *end = s + strlen(s) - 1;

	char tmp = NULL;
	
	while(start < end)
	{
		tmp = *start;
		*start++ = *end;
		*end-- = tmp;
	}
}

int Reverse_Num(int num)
{
	long long int ret = 0;

	while(num)
	{
		ret = ret * 10 + num % 10;
		num /= 10;
	}
	
	if((ret > INT_MAX) || (ret < INT_MIN))
	{
		printf("overflow!\n");
		return -1;
	}

	return ret;
}

void Remove_Dup(char *str)
{
	int len = strlen(str);
	int k = 0;
	int i, j;
	
	for(i = 0; i < len - 1; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(str[i] == str[j])
			{
				break;
			}
		}

		if(j == len)
		{
			str[k++] = str[i];
		}
	}
	str[k] = '\0';
}

void Replace_string(char *str)		//replace ' ' with "%20"
{
	char *p = str;
	int len = strlen(str);

	int num = 0;
	
	while(*p)
	{
		if(*p == ' ')
		{
			num++;
		}
		p++;
	}

	printf("%d\n", num);
	
	int new_len = len + num * 2;
	str[new_len] = '\0';
	new_len--;
	
	for(int i = len - 1; i >= 0; i--)
	{
		if(str[i] == ' ')
		{
			str[new_len] = '0';
			str[new_len - 1] = '2';
			str[new_len - 2] = '%';
			new_len -= 3;
		}
		else
		{
			str[new_len] = str[i];
			new_len--;
		}
	}
}

int Is_Anagrams(char *str1, char *str2)
{
	assert(str1 && str2);
	
	int arr[128] = {0}, i;

	while(*str1)
	{
		for(i = 0; i < 128; i++)
		{
			if(*str1 == i)
			{
				arr[i]++;
				break;
			}
		}
		str1++;
	}
	/*
	for(i = 0; i < 128; i++)
	{
		printf("%d\t", arr[i]);
	}*/
	
	while(*str2)
	{
		for(i = 0; i < 128; i++)
		{
			if(*str2 == arr[i])
			{
				arr[i]--;
				break;
			}
		}
		str2++;
	}

	for(i = 0; i < 128; i++)
	{
		printf("%d\t", arr[i]);
		if(arr[i] != 0)
		{
			return 0;	//no
		}
	}

	return 1;	//yes
}

char *Find_sub(char *str, char *sub)
{
	assert(str && sub);
	
	int i, j, tmp, len_str, len_sub;
	len_str = strlen(str);
	len_sub = strlen(sub);
	
	for(i = 0; i < len_str; i++)
	{
		tmp = i;

		for(j = 0; j < len_sub; j++)
		{
			if(str[tmp++] != sub[j])
			{
				break;
			}
		}

		if(j == len_sub)
		{
			return str + i;
		}
	}

//	printf("ret = %s\n", str);

	return NULL;
}

int main(void)
{
	char *str = (char *)malloc(100);
	strcpy(str,	"show me the!");

#if 0	
	Reverse_String(str);
	printf("%s\n", str);

	int num = 2147483647;
	int ret = Reverse_Num(num);
	printf("%d\n", ret);

	Remove_Dup(str);
	printf("%s\n", str);

	Replace_string(str);
	printf("%s\n", str);

	char *str1 = "show";
	char *str2 = "owsh";
	int ret = Is_Anagrams(str1, str2);
	printf("%d\n", ret);
#endif

	char *ret = Find_sub(str, "w me");
	printf("ret = %s\n", ret);

	return 0;
}

#elif defined Endian

#define MyData (*(volatile unsigned char *)0x22)
int volatile *x = (int *)0x22;

int main(void)
{
	short int i = 0x1122;
	char *c = (char *)&i;

	if(0x22 == *c)
	{
		printf("little endian\n");	//little
	}
	else
	{
		printf("big endian\n");	//big		
	}

	printf("%d\n", sizeof(long long int *));
	
	return 0;
}

#elif defined LinkedList

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

	while(*pp && (*pp)->id != target)
	{
		pp = &(*pp)->next;
	}

	if(*pp == NULL)
	{
		perror("Cannot find the node!");
		return;
	}

	pNode tmp = NULL;
	tmp = *pp;

	*pp = (*pp)->next;

	free(tmp);
	tmp = NULL;
}

void Find_Node(pNode pHead, int target)
{
	assert(pHead);

	while(pHead)
	{
		if(pHead->id == target)
		{
			printf("I'm here!\n");
			
			return;
		}
		else
		{
			pHead = pHead->next;
		}
	}

	if(!pHead)
	{
		printf("Cannot find it\n");
	}
}

pNode Reverse_LinkedList(pNode pHead)
{
	assert(pHead);
	
	pNode p = pHead, pNext = NULL, pPrev = NULL;

	// for head
	pNext = p->next;	
	p->next = NULL;	
	pPrev = pHead;
	p = pNext;

	// for other Nodes
	while(p)
	{		
		pNext = p->next;
		p->next = pPrev;	//point to previous Node		
		pPrev = p;
		p = pNext;
	}
	
	return pPrev;
}

void Create_Circular(pNode pHead, int target)
{
	pNode p = pHead, pCir = NULL;

	while(p && p->id != target)
	{
		p = p->next;
	}

	pCir = p;

	while(p->next)
	{
		p = p->next;
	}

	p->next = pCir;
}

int Has_Circular(pNode pHead)
{
	assert(pHead);
	
	pNode p = pHead, p2 = NULL;

	if(p->next == p)
	{
		return 1;	//yes
	}

	for(; ; p = p->next)
	{
		if(!p)
		{
			return 0;	//no
		}

		if(p->next == pHead)
		{
			return 1;	//yes
		}

		for(p2 = pHead; p2 != p; p2 = p2->next)
		{
			if(p2->next == p->next)
			{
				return 1;	//yes
			}
		}
	}	
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

//	Del_Node(&pHead, 2);
//	showme(pHead);

//	Find_Node(pHead, 38);

//	pHead = Reverse_LinkedList(pHead);
//	showme(pHead);

	Create_Circular(pHead, 5);
//	showme(pHead);

	int ret = Has_Circular(pHead);
	printf("%d\n", ret);
	
	return 0;
}



#else

#endif
