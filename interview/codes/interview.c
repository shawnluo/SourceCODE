
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
/******************** Recursion ******************************
01. Power
02. 
03. 
***************************************************************/

//#define D_10
/******************** others ******************************
01. rotate the image by 90 degrees, and do it in place

***************************************************************/
#define test


#if defined test

//1.1================

int Is_Uniq(char *str)
{
	assert(str);

	if(1 == strlen(str) || 0 == strlen(str))
	{
		return 1;	//yes
	}
	
	char *p = NULL, *p1 = NULL;

	for(p = str; p != '\0'; p++)
	{
		for(p1 = p + 1; p1 != '\0'; p1++)
		{
			if(*p == *p1)
			{
				return 0;	//no
			}
		}
	}
	return 1;	//yes
}
//1.2=================

void My_Reverse(char *str)
{
	assert(str);

	if((0 == strlen(str) || (1 == strlen(str)))
	{
		return;
	}
	
	char *start = str;
	char *end = str + strlen(str) - 1;
	char tmp = NULL;
	
	while(start < end)
	{
		tmp = *start;
		*start = *end;
		*end = tmp;
	}
}

//1.3================

void Remove_Dup(char *str)
{
	assert(str);
	if((2 < strlen(str))
	{
		return;
	}
	
	int i, j;
	int len = strlen(str), tail = 1;
	
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

//1.4================

void swap(char *p, char *q)
{
	char tmp = NULL;

	tmp = *p;
	*p = *q;
	*q = tmp;
}

void My_Sorting(char *str)
{
	int len = strlen(str);

	for(i = 0; i < strlen - 1; i++)
	{
		for(j = 1; j < strlen; j++)
		{
			if(str[i] > str[j])
				swap(str + i, str + j);
		}
	}
}

int Is_Anagrams(char *str1, char *str2)
{
	assert(str1, str2);

	int len1 = strlen(str1);
	int len2 = strlen(str2);	
	if(len1 != len2)
	{
		return no;
	}
	
	My_Sorting(str1);
	My_Sorting(str2);

#if 0
	if(strcmp(str1, str2))
	{
		return yes;
	}
	else
		return no;
#endif

	while(len1++ != 0)
	{
		if(*str1++ != *str2++)
		{
			return no;
		}
	}
	
	return yes;
}

int Is_Anagrams_Ext(char *str1, char *str2)
{
	assert(str1 && str2);

	len1 = strlen(str1);	
	len2 = strlen(str2);
	
	if(0 == len1) && (0 == len2))
	{
		return 1;	//yes
	}
	
	int arr[128] = {0}, i;

	while(*str1 != '\0')
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

	while(*str2 != '\0')
	{
		for(i = 0; i < 128; i++)
		{
			if(*str2 == i)
			{
				arr[i]--;
				break;
			}
		}
		str2++;
	}

	for(i = 0; i < 128; i++)
	{
		if(0 != arr[i])
		{
			return 0;	//no
		}
	}

	return 1;	//yes;
}
//1.5================

void Replace_Character(char *str)
{
	assert(str);
	
	int len = strlen(str);
	int num = 0;	//number of space
	char *p = str;
	
	while(*p)
	{
		if(*p == ' ')
			num++;
		p++;
	}

	new_len = len + 2 * num;
		
	str[new_end] = '\0';

	for(i = len - 1; i >= 0; i--)
	{
		if(p[end] == ' ')
		{
			str[new_len - 1] = '0';
			str[new_len - 2] = '2';
			str[new_len - 3] = '%';
			
			new_len = new_len - 3;
		}
		else
		{
			str[new_len - 1] = str[end];
			new_len = new_len - 1;
		}
	}

}
//1.6=========================

void Rotate_Image(int matrix[n][n], int n)
{
	int layer, i, first, last, top, offset;

	for(i = 0; i <= (n - 1) / 2; i++)
	{
		for(j = i; j < n - 1 - i; j++)
		{
			temp = matrix[i][i];

			matrix[i][j] = matrix[n - 1 - j][i]
			matrix[n - 1 - j][i] = 
		}
	}
}

//1.7============================

void Set_Matrix(int matrix[m][n], int m, int n)
{
	Copy_Matrix(matrix, matrix2, m, n);

	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(0 == matrix[i][j])
			{
				for(x = 0; x < m; x++)
				{
					matrix2[x][j] = 0;
				}
				
				for(y = 0; y < n; y++)
				{
					matrix2[i][y] = 0;
				}
			}
		}
	}

	Copy_Matrix(matrix2, matrix, m, n);
}

//1.8=================================

int Is_Substring_Ext(char *str1, char *str2)
{
	assert();

	len1 = strlen(str1);
	len2 = strlen(str2);

	if(len1 != len2)	return no;
	if(len1 == 0 && len2 == 0)	return yes;

	char *str2_ext = (char *)malloc(len2 * 2);
	strcpy(str2_ext);
	strcat(str2_ext, str2);

	if(Is_Substring(str2_ext, str1))
		return yes;
	else
		return no;
}
//3.0========================================



//5.1=======================================
n: 32bit
m = 10101
i = 6
j = 2

int Set_Bits(int n, int m, int i, int j)
{
	//1. get mask
	int left = ~0 - ((1 << (i + 1)) - 1);
	int right = (1 << j) - 1;
	int mask = left | right;
		
	//2. set mask
	n = n & mask;
	
	//3. set bits
	n = n | (m << j)

	return n;
}

//5.2=======================================
int updateBits(int n, int m, int i, int j)
{
	//1. need clear the bits
	int left = ~0 - ((1 << (j + 1)) - 1)
	
	int mask = left | right;

	n = n & mask;
	
	//2. need set the bits
	n = n | m << i;
}

int Print_Binary(char *str)
{
	assert(str);

	char *p = str;
	char *p_intPart = (char *)malloc(200);
	memset(p_intPart, 0, 200);
	
	while(*p != '\0')
	{
		if(*p == '.')
		{			
			*p_intPart = '\0';
			break;
		}

		*p_intPart++ = *p;
		p++;
	}

	p = str;
	while(*p != '\0' && *p != '.')
	{
		p++;
	}

	char *p_Dec = (char *)malloc(200);

	int intPart = My_Atoi(p_intPart);
	
	while(intPart > 0)
	{
		r = intPart % 2;
		intPart >>= 1;
		int_string = strcat(r, int_string);
	}
}
//5.3==========================================

void Print_Number_Max_Min(int num)
{
	int MAX = int((unsigned)~0) >> 1;
	int MIN = -(int)((unsigned)(~0) >> 1) - 1;
	if(0 == num)
	{
		return;
	}

	int num_ext = num;
	int num_of_one = 0;

	while(num_ext > 0)
	{
		if(num_ext % 2 == 1)
		{
			num_of_one++;
		}
		num_ext >>= 1;
	}

	num_ext = num;
	while(num_ext <= MAX)
	{
		num_ext++;

		if(num_of_one == xx)
		{
			printf(num_ext);
		}
	}
}
//5.4==========================================
//1. way1 - just caculate the number of the 2 integers.
//2. way2 - using Exclusive or
int bitSwapRequired(int a, int b)
{
	int count = 0;

	for(int c = a ^ b; c != 0; c = c >> 1)
	{
		count += c & 1;
	}
	return count;
}
//9.1=========================================
void My_Merge(char *str1, char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	int new_index = len1 + len2 - 1;
	len1--;
	len2--;

	while(len1 >= 0 && len2 >= 0)
	{
		if(str1[len1] > str2[len2])
		{
			str1[new_index--] = str1[len1--];
		}
		else
		{
			str1[new_index--] = str2[len2--];
		}
	}

	while(len2 >= 0)
	{
		str1[new_index--] = str2[len2--];
	}
}

//9.2========================================
void Resorting(char *str[], int num)
{
	//find the anagrams and exchange the position.
}

//9.3========================================
int search(int a[], int first, int last, int target)
{
	while(first <= last)
	{
		int mid = (first + last) / 2;

		if(target == a[mid])
		{
			return mid;
		}
		else if(a[first] <= a[mid])		// case 1
		{
			if(target > a[mid])
			{
				first = mid + 1;
			}
			else if(target >= a[first])
			{
				last = mid - 1;
			}
			else
			{
				first = mid + 1;
			}
		}
		else if(target < a[mid])	// case 2
		{
			last = mid - 1;
		}
		else if(target <= a[last])
		{
			first = mid + 1;
		}
		else
		{
			last = mid - 1;
		}
	}
	
	return -1;
}

//2.1========================================

void Remove_Node(pNODE *pHead, int id)
{
	assert(*pHead);

	pNODE *p = pHead;

	while(*p && (*p)->id != id)
	{
		p = &(*p)->next;
	}

	pNODE tmp = *p;
	*p = (*p)->next;

	free(tmp);
	tmp = NULL;
}

void deleteDups(pNODE pHead)
{
	assert(pHead);
	
	if(NULL == pHead->next)
	{
		return;
	}

	pNODE p = pHead;
	pNODE pNext = NULL;
	
	for(p = pHead, p != NULL; p = p->next)
	{
		for(pNext = p->next; pNext != NULL; pNext = pNext->next)
		{
			if(p->id == pNext->id)
			{
				Remove_Node(&pHead, pNext->id);
			}
		}
	}
}

//=========================================

#define BIG_ENDIAN		1
#define LITTLE_ENDIAN	0
int Big_Or_Little()
{
	short int WORD;
	char *c = (char *)&WORD;

	if(*c == 1)
	{
		LITTLE_ENDIAN;
	}
	else
	{
		BIG_ENDIAN;
	}
}

int volatile *reg = (int *)0x8000000;

if(Enable == TRUE)
{
	*reg |= (1 << ENABLE_BIT);
}
else
{
	*reg &= ~(1 << ENABLE_BIT);
}

int volatile *reg = (int *)0x80000000;

if(Enable == TRUE)
{
	*reg |= (1 << ENABLE_BIT);
}
else
{
	*reg &= ~(1 << ENABLE_BIT);
}


//set the volume
//1. clear the bits first
mask = 0;
mask = (0xff) << 8;
*reg &= ~mask;

//2. set the bits
*reg |= data;

reverse(char *str)
{
	assert();

	char *start = str;
	*end = str + strlen;

	while(start < end)
	{

		start++;
		end--;
	}
}

bit = (num >> x) & 1;
num ^= 1 << x;

Quick_Sorting(int arr [ ],int start,int end)
{
	if(start < end)
	{
		left = start + 1;
		right = end;

		while(left <= right)
		{
			
		}
	}
}

strstr(string, substring)
{
	assert();
	
	char *p = string;
	
	for(p = string; *p != '\0'; p++)
	{
		tmp = p;
		
		for(p_sub = substring; p_sub != '\0'; p_sub++)
		{
			if(*p++ != *p_sub)
				break;
		}

		if(*p_sub == '\0')
			return yes;
	}

	return no;
}

Insert_Node_Front(pNODE * ppHead,int target_id,int new_id)
{
	assert();
	
	pNODE *pp = ppHead;

	while(*pp && (*pp)->id != target_id)
	{
		pp = &(*pp)->next;
	}

	pNODE newNode = (pNODE)malloc(LEN);
	newNode->next = (*pp)->next;
	newNode->id = new_id;
	*pp = newNode;
}

int Power(int m, int n)
{
	if(n == 0)
	{
		return 1;
	}
	else if(n == 1)
	{
		return m;
	}

	if((n % 2) == 0)
	{
		ret = Power(m, n / 2);
		result = ret * ret;
	}
	else
	{
		ret = Power(m, n / 2);
		result = ret * ret *m;
	}

	return result;
}


int main(void)
{
	for(int i = 0; i <= (n - 1) / 2; i++)
	{
		for(j = 1; j < n - 1 - i; j++)
		{
			int tmp = arr[i][j];

			arr[i][j] 					= arr[n - 1 - j][i];
			arr[n - 1 - j][i] 			= arr[n - 1 - i][n - 1 - j];
			arr[n - 1 - i][n - 1 - j]	= arr[n - 1 - n + 1 + j][n - 1 - i];
			arr[j][n - 1 - i]			= tmp;
		}
	}
	
	return 0;
}

#elif defined bigEnd_littleEnd

int main(void)
{
	unsigned char i = 1;
	char *c = (char *)&i;

	if(*c)
	{
		little;
	}
	else
		big;

	return 0;
}

#elif defined xx
//" " be replaced with "%20"
void Replace_char(char *str)
{
//	assert();

	int len_str = strlen(str);
	int num = 0;
	int new_len;
	
	char *p = str;
	
	while(*p != '\0')
	{
		if(*p == ' ')
		{
			num++;
		}
		p++;
	}
	new_len = len_str + 2 * num;
	*(p + new_len + 1) = '\0';

	int i = 0;
	p = str;

	for(i = len_str - 1; i >= 0; i--)
	{
		if(*(p + i) == ' ')
		{
			str[new_len - 1] = '0';
			str[new_len - 2] = '2';
			str[new_len - 3] = '%';
			new_len -= 3;
		}
		else
		{
			str[new_len - 1] = str[i];
			new_len -= 1;
		}
	}
}

int main(int argc, char *argv[])
{
	char *str = (char *)malloc(20);
	strcpy(str,	"a b");
	
	Replace_char(str);
	printf("%s\n", str);
	
	return 0;
}

#elif defined D_xx	//sorting
void Swap(int *x, int *y)
{
	int tmp;
	
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void Bubble_Sorting(int arr[], int len)
{
	int i, j;

	for(i = 0; i < len - 1; i++)
	{
		for(j = i + 1; j < len; j ++)
		{
			if(arr[i] < arr[j])
			{
				Swap(&arr[i], &arr[j]);
			}
		}
	}
}

//star, end, left, right: All are orders of array member
void Quick_Sorting(int arr[], int start, int end)
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
				Swap(&arr[left], &arr[right]);
			}
		}
		Swap(&arr[start], &arr[right]);
		
		Quick_Sorting(arr, start, right - 1);
		Quick_Sorting(arr, right + 1, end);
	}
}

int main(int argc, char *argv[])
{
	int arr[] = {1, 22, 3, 111, 76,54};
	int len = sizeof(arr) / sizeof(arr[0]);
	
	Bubble_Sorting(arr, len);

	for(int i = 0; i < len; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
	
	return 0;
}

#elif defined D_02
char *reverse(char *str)
{
	assert(str);

	if(strlen(str) <= 1)
	{
		return str;
	}
	
	char tmp;
	char *start = str, *end = NULL;
	end = str + strlen(str) - 1;
	
	while(start < end)
	{
		tmp = *start;
		*start++ = *end;
		*end-- = tmp;
	}

	return str;
}

char *reverse_ext(char *str)
{
	assert(str);
	
	if(strlen(str) <= 1)
	{
		return str;
	}
	
	int i, len = strlen(str);
	char tmp = NULL;
	char *p = str;
	
	for(i = 0; i < len / 2; i++)
	{
		tmp = *(p + i);
		*(p + i) = *(p + len - 1 - i);
		*(p + len - 1 - i) = tmp;
	}
	
	return str;
}

int Is_Palindrome(char *str)
{
	assert(str);

	if(strlen(str) <= 1)
	{
		return 1;
	}
	
	char *start, *end;
	start = str;
	end = str + strlen(str) - 1;
	
	while(start < end)
	{
		if(*start++ != *end--)
		{
			return 0;	
		}
	}

	return 1;
}

// 2 strings, there is 1 additional character in the one string.
char Find_Additional(char *str1, char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	
	if((len1 == len2) || (abs(len1 - len2) > 1))
	{
		perror("wrong strings!");
		exit(-1);
	}
	
	char *p1 = str1;
	char *p2 = str2;
	char ret = NULL;

	strcat(p1, p2);
	printf("%s\n", p1);

	int len = len1 + len2;
	
	while(len--)
	{
		ret ^= *p1++;
		
		printf("%c\n", ret);
	}

	return ret;
}


// Is str2 substring of str1?
char *Find_Substring(char *str1, char *str2)
{
	assert(str1 && str2);
	
	char *pTmp = NULL;
	
	for( ; *str1 != '\0'; str1++)
	{
		pTmp = str1;

		for( ; *str2 != '\0'; str2++)
		{
			if(*str2 != *pTmp++)
			{
				break;
			}
		}

		if(*str2 == '\0')
		{
			return str1;
		}
	}

	printf("Cannot find it\n");
	
	return NULL;
}

void Remove_Dup(char *str)
{
	assert(str);

	if(1 == strlen(str))
	{
		return;
	}
	
	int len = strlen(str);
	int new = 0;
	int i, j;
	
	for(i = 0; i < len; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(str[i] == str[j])
			{
				break;
			}
		}
		
		if(str[j] == '\0')
		{
			str[new++] = str[i];
		}
	}
	
	str[new] = '\0';
}

void Remove_Dup_Ext(char *str)
{
	assert(str);
	
	if(1 == strlen(str))
	{
		return;
	}
	
	int i, j;
	
	for(i = 0; i < strlen(str); i++)
	{
		for(j = i + 1; j < strlen(str); j++)
		{
			if(str[i] == str[j])
			{
				memmove(str + j, str + j + 1, strlen(str + j + 1) + 1);
				j--;
			}
		}
	}
}

//anagrams: aabc  abac
int Same_Char(char *str1, char *str2)
{
	assert(str1 && str2);

	if(length is not the same)
		return 0;
	
	int i = 0;
	int arr[128] = {0};
	char *p = str1;	
	
	while(*p != '\0')
	{
		for(i = 0; i < 128; i++)
		{
			if(i == *p)
			{
				arr[i]++;
			}
		}
		p++;
	}

	p = str2;
	while(*p != '\0')
	{
		for(i = 0; i < 128; i++)
		{
			if(i == *p)
			{
				arr[i]--;
			}
		}
		p++;
	}

	for(i = 0; i < 128; i++)
	{
		if(arr[i] != 0)
		{
			return 0;	//no
		}
	}
	
	return 1;	//yes
}

int main(int argc, char *argv[])
{
	char *str = (char *)malloc(20);
	memset(str, 0, 20);
	strcpy(str, "");

	char *ret = reverse_ext(str);
	printf("%s\n", ret);

	int ret_2 = Is_Palindrome(str);
	printf("ret = %d\n", ret2);

//=========================
	char *strx = "ababx";

	int ret = Is_Palindrome(strx);

//	printf("ret = %d\n", ret);

	char *str1 = (char*)malloc(20);
	strcpy(str1, "show321me");
	char *str2 = "sh!ow123me";

	char addi = Find_Additional(str1, str2);
	printf("addi = %c\n", addi);

//==================================
	char *str1 = "showmethemoney";
	char *str2 = "tdhe";

	char *Sub = Find_Substring(str1, str2);
	printf("Sub is %s\n", Sub);

	return 0;
}

#elif defined test1

int main(int argc, char *argv[])
{
	pid_t childPID;
	int var_lcl = 0;

	childPID = fork();

	if(childPID >= 0)
	{
		if(0 == childPID)	//child process
		{
			
		}
		else				//parent process
		{

		}
	}
	else					//fork failed
	{
		exit(-1);
	}
}

#elif defined D_01

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

#elif defined D_04
int Power(int m, int n)
{
	int ret = 0;
	int result = 0;

	if(0 == n)
	{
		return 1;
	}

	if(1 == n)
	{
		return m;
	}

	if((n % 2) == 0)
	{
		ret = Power(m, n / 2);
		result = ret * ret;
	}
	else
	{
		ret = Power(m, n / 2);
		result = ret * ret *m;
	}
	
	return result;
}

void rec(int x)
{
	if(x > 0)
	{
		printf("before: %d\n", x);
		rec(x - 1);
		rec(x - 1);
		printf("after: %d\n", x);		
	}
}

int main(int argc, char *argv[])
{
	
	int x = Power(3, 4);
	printf("x = %d\n", x);

	rec(3);
	
	return 0;
}
#elif defined D_0x

#define ENABLE_BIT 0x07			//bit7
#define VOLUME_START_BIT 0x1f	//bit8
#define VOLUME_END_BIT 0xf0		//bit15

void Control_Sound(int Volume, bool Enable)
{
	int i = 0, data = 0, mask = 0;

	int volatile *reg = (int *)0x80000000;

	//enable the control
	if(TRUE == Enable)
	{
		*reg |= 1 << ENABLE_BIT;
	}
	else
	{
		*reg &= ~(1 << ENABLE_BIT);
	}

	//set the volume
	if((Volume >= 0) && (Volume <= 255))
	{
		data = Volume;
		data <<= 8;

		//clear bit8-15
		mask = 0;
		mask = 0xff << 8;

		*reg &= ~mask;

		//set bit8-15
		*reg |= data;
	}
}

int main(int argc, char *argv[])
{
	Control_Sound(5, 1);
}

#else

#endif
