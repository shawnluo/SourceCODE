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

#define test

#if defined test

int Is_Pal(char *str)
{
	assert(str);
	
	char *start = str;
	char *end = str + strlen(str) - 1;

	while(start < end)
	{
		if(*start++ != *end--)
		{
			return 0;	//no
		}
	}
	
	return 1;	//yes
}

int main(void)
{
	char *str = "sx";
	
	int ret = Is_Pal(str);
	printf("ret = %d\n", ret);
	
	return 0;
}

#elif defined xx
pNode FindCommonStr(char *str1, char *str2)
{
	char *p1;// = str1;
	char *p2;// = str2;
	char *tmp;
	
	for(p1 = str1; *p1; p1++)
	{
		tmp = p1;
		
		for(p2 = str2; *p2; p2++)
		{
			if(*tmp++ != *p2)
			{
				break;
			}
			else
			{
				
			}
		}
	}
}

char *Longest_Common_Str(char *str1, char *str2)
{
	//1. find out the common strs and put them into LL
	FindCommonStr(str1, str2);
	
	//2. find the longest
}

int main(void)
{
	Longest_Common_Str("showme", "goodayow");
	
	return 0;
}

#elif defined fd
void remove_dup(char *str)
{
	assert(str);
	
	int i, j;
	
	for(i = 0; i < strlen(str) - 1; i++)
	{
		for(j = i + 1; j < strlen(str); j++)
		{
			if(str[i] == str[j])
			{
				memmove(str + j, str + j + 1, strlen(str + j + 1) + 1);
			}
		}
	}
}

void remove_dup_ext(char *str)
{
	assert(str);

	int i, j, len = strlen(str);
	int tail = 1;	

	for(i = 1; i < len; i++)
	{
		for(j = 0; j < tail; j++)
		{
			if(str[i] == str[j])
			{
				break; 
			}
		}

		if(j == tail)
		{
			str[tail++] = str[i];
		}
	}

	str[tail] = '\0';
}

void repl(char *str, char str2, char *str3)
{
	int len = strlen(str);
	int x;

	char *p = str;
	
	while(p)
	{
		if(*p++ == str2)
		{
			x++;
		}
	}

	int newlen = len - x + strlen(str3) * x;
	str[newlen] = '\0';

	for(int i = len - 1; i >= 0; i-- )
	{
		if(str[i] == str2)
		{
			str[newlen - 1] = '0';
			str[newlen - 2] = '2';
			str[newlen - 3] = '%';
			newlen -= 3;
		}
		else
		{
			str[newlen - 1] = str[i];
			newlen -= 1;
		}
	}
}

#if 0
int Is_ana(char *str1, char *str2)
{
	assert(str1 && str2);

	int len1 = strlen(str1);
	int len2 = strlen(str2);

	if(len1 != len2)
	{
		return 0;
	}
	
	int i, j;

	for(i = 0; i < len1; i++)
	{
		for(j = )
	}
}
#endif
int main(void)
{
//	char *str = (char *)malloc(20);
//	strcpy(str, "egoodeaytodie");

	char str[144];
	memset(str, 0, sizeof(str));
	strcpy(str, "egoodeaytodie");

	remove_dup(str);
	printf("ret = %s\n", str);
	
	return 0;
}

#elif defined x03_quickSort
void swap(int *x, int *y)
{
	int tmp = 0;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void quick_sort(int data[], int start, int end)
{
	int left, right;// = start + 1, right = end;

	if(start < end)
	{
		left  = start + 1;
		right = end;
		
		while(left <= right)
		{
			while(data[left] <= data[start])
			{
				left++;
			}

			while(data[right] > data[start])
			{
				right--;
			}
			
			if(left < right)
			{
				swap(&data[left], &data[right]);
			}
		}

		swap(&data[start], &data[right]);
		
		quick_sort(data, start, right - 1);
		quick_sort(data, right + 1, end);	
	}
}

void showme(int data[], int num)
{
	int i;

	for(i = 0; i < num; i++)
	{
		printf("%d\t", data[i]);
	}
	
	printf("\n");
}

int main(void)
{
	int data[] = {1111, 21, 12, 762, 220, 65};

	quick_sort(data, 0, 5);
	showme(data, 6);
}

#elif defined x02_testvolatile
int main(void)
{
	int i = 10;

	int volatile *x = (int *)&i;
	printf("x = %d\n", *x);
	
	return 0;
}

#elif defined x01_insertion_sort
void swap(int *x, int *y)
{
	int tmp = 0;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void Insertion_sort(int data[], int num)
{
	int i, j, tmp;

	for(i = 0; i < num - 1; i++)
	{
		tmp = i + 1;
		if(data[tmp] < data[i])
		{
			for(j = 0; j < i; j++)
			{
				if(data[tmp] < data[j])
				{
					swap(&data[tmp], &data[j]);
				}
			}
		}
	}
}

void showme(int data[], int num)
{
	int i;

	for(i = 0; i < num; i++)
	{
		printf("%d\t", data[i]);
	}
	
	printf("\n");
}

int main(void)
{
	int data[] = {11, 2, 43, 987, 0, 9};
	
	Insertion_sort(data, sizeof(data) / sizeof(data[0]));
	showme(data, sizeof(data) / sizeof(data[0]));
	
	return 0;
}

#elif defined xx
typedef struct node
{
	int id;
	struct node *next;
} Node, *pNode;

#define LEN sizeof(Node)

pNode Create_LL(int data[], int size)
{
	pNode pHead = NULL;
	pNode p = NULL, p1 = NULL;

	for(int i = 0; i < size; i++)
	{
		if(i == 0)
		{
			pHead = p = (pNode)malloc(LEN);
			p->id = data[i];
			p->next = NULL;
			
			p1 = p;
		}
		else
		{
			p = (pNode)malloc(LEN);
			p->id = data[i];
			p->next = NULL;
			
			p1->next = p;
			
			p1 = p;
		}
	}
/*	
	while(size--)
	{
		p = (pNode)malloc(LEN);
		p->id = data[size];
		p->next = pHead;
		pHead = p;
	}
*/
	return pHead;
}

void Insert_Node_Front(pNode *ppHead, int num, int target)
{
	assert(*ppHead);
	
	pNode *pp = ppHead;

	while(*pp && (*pp)->id != target)
	{
		pp = &(*pp)->next;
	}
	
	if(!*ppHead)
	{
		printf("Cannot find the node!\n");
		return;
	}

	pNode new = (pNode)malloc(LEN);
	new->id = num;

	new->next = *pp;
	*pp = new;
}

void Insert_Node_Behind(pNode *ppHead, int num, int target)
{
	assert(*ppHead);

	pNode *pp = ppHead;

	while(*pp && (*pp)->id != target)
	{
		pp = &(*pp)->next;
	}

	if(!*pp)
	{
		printf("Cannot find it!\n");
		return;
	}

	pNode new = (pNode)malloc(LEN);
	new->id = num;

	new->next = (*pp)->next;
	(*pp)->next = new;
}

void Del_Node(pNode *ppHead, int target)
{
	assert(*ppHead);

	pNode *pp = ppHead;

	while(*pp && (*pp)->id != target)
	{
		pp = &(*pp)->next;
	}

	if(!*pp)
	{
		printf("Cannot find it!\n");
		return;
	}

	pNode tmp = *pp;

	*pp = (*pp)->next;

	free(tmp);
	tmp = NULL;
}

void Del_LL_FromTo(pNode *ppHead, int start, int end)
{
	int i = 0;
	pNode *pp = ppHead;

	for(i = 0; i < start; i++)
	{
		pp = &(*pp)->next;
	}
	
	for(i = start; i < end; i++)
	{
		Del_Node(pp, (*pp)->id);
	}
}

void Del_LL(pNode *ppHead)
{
	pNode *pp = ppHead;
	
	while(*pp)
	{
		Del_Node(ppHead, (*pp)->id);
	}
}

pNode Reverse_LL(pNode pHead)
{
	assert(pHead);

	pNode p = pHead, pL = NULL, pR = NULL;

	p = pHead->next;
	pL = pHead;
	pL->next = NULL;

	while(p)
	{
		pR = p->next;	//save pR

		p->next = pL;	//reverse p->next
		pL = p;
		p = pR;
	}

	return pL;
}

void Create_Circular(pNode pHead, int target)
{
	assert(pHead);
	
	pNode p = pHead;
	pNode tail = NULL;

	while(p && p->id != target)
	{
		p = p->next;
	}

	if(!p)
	{
		printf("Cannot find the target!\n");
		return;
	}

	tail = p;
	while(tail->next)
	{
		tail = tail->next;
	}
	tail->next = p;
}

int Has_Circular(pNode pHead)
{
	assert(pHead);
	
	pNode p = pHead;
	pNode p2 = pHead;

	int ret = 0;
	
	for(p = pHead; ;p = p->next)
	{
		if(!p)
		{
			return 0;
		}
		
		if(p2->next == pHead)
		{
			return 1;	//yes
		}
		
		for(p2 = pHead; p2 != p; p2 = p2->next)
		{
			if(!p2)
			{
				return 0;	//no
			}

			if(p2->next == p->next)
			{
				return 1;	//yes
			}
		}
	}
}

void swap(int *x, int *y)
{
	int tmp = 0;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

pNode Merge_LL(pNode pHead1, pNode pHead2)
{
	assert(pHead1 && pHead2);

	pNode p = pHead1, p2 = NULL;

	while(p->next)
	{
		p = p->next;
	}
	
	p->next = pHead2;

/*	bubble sorting
	for(p = pHead1; p; p = p->next)
	{
		for(p2 = p->next; p2; p2 = p2->next)
		{
			if(p->id > p2->id)
			{
				swap(&p->id, &p2->id);
			}
		}
	}
*/
//	insertion sorting
	for(p = pHead1; p; p = p->next)
	{
		
	}

	return pHead1;
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
	int data[][5] = {
		{1, 2, 3, 4, 5},
		{61, 7, 8, 19, 10},
		{111, 12, 153, 14, 15}};

	pNode pHead = Create_LinkedList(data[0], sizeof(data[0]) / sizeof(data[0][0]));
	showme(pHead);

/*	Del_LL_FromTo(&pHead, 0, 4);
	showme(pHead);
*/	
/*	Insert_Node_Front(&pHead, 4440, 1);
	showme(pHead);
	
	Insert_Node_Behind(&pHead, 555, 5);
	showme(pHead);

	Del_Node(&pHead, 555);
	showme(pHead);
	
	pHead = Reverse_LL(pHead);
	showme(pHead);
*/
//	Create_Circular(pHead, 2);
//	showme(pHead);
	
/*	int ret = Has_Circular(pHead);
	printf("ret = %d\n", ret);
*/

/*	Del_LL(&pHead);
	showme(pHead);
*/

	pNode pHead1 = Create_LinkedList(data[1], sizeof(data[1]) / sizeof(data[1][0]));
	pNode pHead2 = Create_LinkedList(data[2], sizeof(data[2]) / sizeof(data[2][0]));

	pHead = Merge_LL(pHead1, pHead2);
	showme(pHead);

	return 0;
}
#endif
