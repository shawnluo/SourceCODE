
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

/*************************
*		demo
*************************/
//#define d_01	//show the usage of strcpy and strncpy
//#define d_02	//find and return the substring
//#define d_03	//bit operations
//#define d_04	//find the addtional charater
//#define d_05	//linklist and sorting
//#define d_06	//quick sorting
//#define sorting_02	//insertion sorting
//#define d_07	//Is_Palindrome
//#define d_08	//2 linklists adding with carry bit
//#define d_09	//substring or not
//#define d_10	//the linked lists with circular
//#define d_11	//the double pointer && 2 dimensional array
//#define d_12	//rotate 90 degree in place
//#define d_13	//same string but in different order
//#define d_14	//find the onlyone
//#define d_15	//reverse a interger, beware of overflow
//#define d_16	//dynamically allocate a 2D array
//#define d_17	//thread demo
//#define Demos_ArraysStrings
//#define Demo_semaphore

//#define test_pre
#define test
//#define test_2
//#define test_3


void print_trace()
{
//    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

#ifdef test

Is_Uniq(char *s1)
{
	
}

int main(void)
{
	return 0;
}

#elif defined test_1

typedef struct stu
{
	int id;
	struct stu *next;
} STU;

#define LEN sizeof(STU)

STU *create_Linkedlist(int data[], int len)
{
	STU *head = NULL, *p = NULL;

	while(--len >= 0)
	{
		p = (STU *)malloc(LEN);
		p->id = data[len];
		p->next = head;
		head = p;
	}

	return head;
}

void insert_Node_Front(STU **head, int Target, int New)
{
	STU **p = head;
	STU *newNode = NULL;

	while(*p && (*p)->id != Target)
	{
		p = &(*p)->next;
	}

	STU *tmp = *p;
	newNode = (STU *)malloc(LEN);
	newNode->id = New;
	*p = newNode;
	newNode->next = tmp;
}

void insert_Node_Behind(STU **head, int Target, int New)
{
	STU **p = head;
	STU *newNode = NULL;

	while(*p && (*p)->id != Target)
	{
		p = &(*p)->next;
	}

	STU *tmp = (*p)->next;
	newNode = (STU *)malloc(LEN);
	newNode->id = New;
	(*p)->next = newNode;
	newNode->next = tmp;
}

void showme(STU *head)
{
	while(head)
	{
		printf("%d\t", head->id);
		head = head->next;
	}
	printf("\n");
}

int main(void)
{
	int data[3][5] = {{1, 2, 3, 4, 5},
					{6, 7, 8, 9, 10}, 
					{11, 12, 13, 14, 15}};

	STU *head = create_Linkedlist(data[0], sizeof(data[0]) / sizeof(data[0][0]));
	insert_Node_Front(&head, 5, 100);
	showme(head);
	insert_Node_Behind(&head, 1, 300);
	showme(head);	
	return 0;
}

#elif defined d_17
pthread_t tid1, tid2;

void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, \
		(unsigned int)tid, (unsigned int)tid);
}

void *thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
//	return ((void *)0);
	sleep(50);
	pthread_exit((void *)1);
//	exit(1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
	pthread_cancel(tid1);
	pthread_exit((void *)2);
}

int main(void)
{
	int err;
	void *tret;
	
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if(err != 0)
	{
		perror("can't create thread");
	}

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if(err != 0)
	{
		perror("can't create thread");
	}

//	printids("main thread: ");
	sleep(2);

	err = pthread_join(tid1, &tret);
	if(err)
	{
		error("can't join with thread1\n");
	}
	printf("thread1 exit code %d\n", (int)tret);
	
	return 0;
}
#elif defined d_16
#if 0
int main(void)
{
	int r = 3, c = 4;
	int *arr = (int *)malloc(r * c * sizeof(int));
	
	int i, j, count = 0;

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			*(arr + i * c + j) = ++count;
		}
	}
	
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d ", *(arr + i * c + j));
		}
	}

	return 0;
}
#endif

#if 0
int main(void)
{
	int r = 3, c = 4, i, j, count;
	int *arr[r];

	for(i = 0; i < r; i++)
	{
		arr[i] = (int *)malloc(c * sizeof(int));
	}

	count = 0;

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			arr[i][j] = ++count;	//*(*(arr + i) + j) = ++count;
		}
	}

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d ", arr[i][j]);
		}
	}

	return 0;
}
#endif

#if 0
int main()
{
	int r = 3, c = 4, i, j, count;

//	int (*arr)[c];
	int **arr = (int **)malloc(r * sizeof(int *));
	for(i = 0; i < r; i++)
	{
		arr[i] = (int *)malloc(c * sizeof(int));
	}

	count = 0;	
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			arr[i][j] = ++count;
		}
	}

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d ", arr[i][j]);
		}
	}
	return 0;
}
#endif

int main(void)
{
	int r = 3, c = 4;
	int **arr;
	int count = 0, i, j;

	arr = (int **)malloc(sizeof(int *) * r);
	arr[0] = (int *)malloc(sizeof(int) * c * r);

	for(i = 0; i < r; i++)
	{
		arr[i] = (*arr + c * i);
	}

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			arr[i][j] = ++count;
		}
	}

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d ", arr[i][j]);
		}

	}
	return 0;
}

#elif defined d_15
int My_Reverse(int num)
{
	int ret = 0, sign = num >> 31;
	
	while(num != 0)
	{
		ret = ret * 10 + num % 10;
		num = num / 10;
	}

	if(sign != (ret >> 31))
	{
		printf("overflow!\n");
		exit(1);
	}
	
	return ret;
}

int main(void)
{
	int num = My_Reverse(100100);
	printf("%d\n", num);

	int i = 1000000003;
	printf("i >> 31: %d\n%d\n", i>>31, INT_MAX);
	printf("%d\n", CHAR_BIT);
	printf("%llu\n", ((unsigned long long)1 << 32) - 1);
	return 0;
}

#elif defined d_14

int Find_OnlyOne(int arr[], int len)
{
	int tmp = arr[0];
	
	for(int i = 1; i < len; i++)
	{
		tmp ^= arr[i];
	}
	return tmp;
}

int main(void)
{
	int arr[] = {1, 1, 2, 2, 30};
	int ret = Find_OnlyOne(arr, sizeof(arr) / sizeof(arr[0]));

	printf("ret = %d\n", ret);
}

#elif defined d_13
int Is_Samestring(char *str1, char *str2)
{
	assert(str1 && str2);

	int Len1 = strlen(str1);
	int Len2 = strlen(str2);

	if(Len1 != Len2)
	{
		return 0;	//NO
	}
	
	int i, j;
	char *tmp = (char *)malloc(Len2);
	tmp = strcpy(tmp, str2);

	for(i = 0; i < Len1; i++)
	{
//		tmp = str1 + i;
		for(j = 0; j < Len2; j++)
		{
			if(*(str1 + i) == *(tmp + j))
			{
				memmove(tmp + j, tmp + j + 1, strlen(tmp + j + 1) + 1);
				break;
			}
		}
		if(j == Len2)
		{
			return 0;
		}
	}

	if(i == Len1)
	{
		return 1;	//YES
	}
}

int main(void)
{
	int i, j;

	char *str1 = "showme";
	char *str2 = "ewomsh";

	int ret = Is_Samestring(str1, str2);
	printf("%d\n", ret);
	
    return 0;
}

#elif defined d_12
int num = 5;

void rotate_1(int (*mat)[num], int n)   //40 degree mirror from left up to right down
{
    int i = 0, j = 0, tmp;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= i; j++)
        {
//			printf("%d\t%d\n", *(*(mat + i) + j), *(*(mat + j) + i));
            tmp               = *(*(mat + i) + j);
            *(*(mat + i) + j) = *(*(mat + j) + i);
            *(*(mat + j) + i) = tmp;
        }
    }

//	*(*(mat + 1) + 1) = 100;
}

void rotate_2(int mat[5][5], int n)
{
    for (int layer = 0; layer < n / 2; layer++)
    {
        int first = layer;
        int last  = n - 1 - layer;

        for (int i = first; i < last; i++)
        {
            int offset = i - first;
            int top    = mat[first][i];

            //left -> top
            mat[first][i] = mat[last - offset][first];

            //bottom -> left
            mat[last - offset][first] = mat[last][last - offset];

            //right -> bottom
            mat[last][last - offset] = mat[i][last];

            //top -> right
            mat[i][last] = top;
        }
    }
}

void rotate_3(int mat[5][5], int n)
{
    int row, col, tmp[5][5];

    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            tmp[row][col] = mat[n - 1 - col][row];
        }
    }

    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            mat[row][col] = tmp[row][col];
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

int main(void)
{
    int n = 5, i, j;
    int mat[5][5] = { {  1,  2,  3,  4,  5 },
                      {  6,  7,  8,  9, 10 },
                      { 11, 12, 13, 14, 15 },
                      { 16, 17, 18, 19, 20 },
                      { 21, 22, 23, 24, 25 } };

    showme(mat, n);
    printf("\n");

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
//			printf("%d\t", *(*(p + i) + j));
        }
//		printf("\n");
    }

    printf("\n");

//	printf("sizeof(mat) is: %d\n", sizeof(mat));


//	rotate_1(mat, n);
//	showme(mat, n);

    printf("\n");

//	rotate_2(mat, n);
//	showme(mat, n);

    printf("\n");

    rotate_3(mat, n);
    showme(mat, n);
}

#elif defined t5
void my_Rep(char *str, char *rep)
{
    int i = 0, num = 0;
//	char *p[];	//1. create new char string by space; 2. add "rep" on the end of new strings; 3. assemble
    int len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            num++;
        }
    }

    int new_Len = len - num + num * 3;

    str[new_Len] = '\0';

    for (i = len - 1; i >= 0; i--)
    {
        if (str[i] == ' ')
        {
            str[new_Len - 1] = '0';
            str[new_Len - 2] = '2';
            str[new_Len - 3] = '%';
            new_Len         -= 3;
        }
        else
        {
            str[new_Len - 1] = str[i];
            new_Len         -= 1;
        }
    }
}

int main(void)
{
    char *str = (char *)malloc(200);

    strcpy(str, "haha you're so good");

    char *rep = "%20";

    my_Rep(str, rep);

    printf("%s\n", str);

    return 0;
}

#elif defined t4
int Is_Ana(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2))
    {
        return 0;               //no
    }

    int i, j;

    for (i = 0; i < strlen(str1); i++)
    {
        for (j = 0; j < strlen(str2); j++)
        {
            if (str1[i] == str2[j])
            {
                break;
            }
        }

        if (j == strlen(str2))
        {
            return 0;                   //no
        }
    }

    return 1;           //yes
}

int main()
{
    char *str1 = "good";
    char *str2 = "odog";
    int  ret   = Is_Ana(str1, str2);

    printf("%d\n", ret);
    return 0;
}

#elif defined t3

void remove_Dup(char *str)
{
    if (str)
    {
        return;
    }

    int i, j, new_Len = 1;
    int len = strlen(str);

    for (i = 1; i < len; i++)
    {
        for (j = 0; j < new_Len; j++)
        {
            if (str[i] == str[j])
            {
                break;
            }
        }

        if (j == new_Len)
        {
            str[new_Len++] = str[i];
        }
    }
    str[new_Len] = '\0';
}

int main(void)
{
    char *str = (char *)malloc(20);

    strcpy(str, "sssosgoodx");

    remove_Dup(str);
    printf("%s\n", str);
    return 0;
}

#elif defined t2

void reverse(char *str)
{
    int  len = strlen(str);
    int  i;
    char tmp;

    for (i = 0; i < (len + 1) / 2; i++)
    {
        tmp                  = *(str + i);
        *(str + i)           = *(str + len - 1 - i);
        *(str + len - 1 - i) = tmp;
    }
}

int main(void)
{
    char *str = (char *)malloc(20);

    strcpy(str, "showme");

    reverse(str);

    printf("%s\n", str);
}

#elif defined t1
int Is_Unique(char *str)
{
    int i, j, len;

    len = strlen(str);

    if (len == 0)
    {
        printf("the length of str is 0\n");
        return 1;               //yes
    }

    for (i = 0; i < len - 1; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (*(str + i) == *(str + j))
            {
                return 0;                       //no
            }
        }
    }

    return 1;           //yes
}

int main(void)
{
    char *str = "abcqa";
    int  len  = strlen(str);
    int  ret  = Is_Unique(str, len);

    printf("%d\n", ret);

    return 0;
}

#elif defined bit_operations

#elif defined d_11
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
    int n = 5, i, j;
    int mat[n][n] = { {  1,  2,  3,  4,  5 },
                      {  6,  7,  8,  9, 10 },
                      { 11, 12, 13, 14, 15 },
                      { 16, 17, 18, 19, 20 },
                      { 21, 22, 23, 24, 25 } };

    showme(mat, n);
    printf("\n");

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

    printf("sizeof(mat) is: %d\n", sizeof(mat));


    rotate(mat, n);
//	showme(mat, n);
}

#elif defined d_10
typedef struct stu
{
    int        id;
    struct stu *next;
} STU;

#define LEN    sizeof(STU)

STU *create_Linkedlist(int data[], int len)
{
    STU *head = NULL, *p = NULL, *p1 = NULL;

    head       = (STU *)malloc(LEN);
    head->id   = data[0];
    head->next = NULL;
    p1         = head;

    for (int i = 1; i < len; i++)
    {
        p        = (STU *)malloc(LEN);
        p->id    = data[i];
        p->next  = NULL;
        p1->next = p;
        p1       = p;
    }

    return head;
}

STU *create_Linkedlist_Circular(int data[], int len)
{
    STU *head = NULL, *p = NULL, *p1 = NULL;
    STU *tmp = NULL;

    head       = (STU *)malloc(LEN);
    head->id   = data[0];
    head->next = NULL;
    p1         = head;

    for (int i = 1; i < len; i++)
    {
        p        = (STU *)malloc(LEN);
        p->id    = data[i];
        p->next  = NULL;
        p1->next = p;
        p1       = p;

        if (i == 3)
        {
            tmp = p;
        }
    }
    p->next = tmp;

    return head;
}

STU *create_Linkedlist_EXT(int data[], int len)
{
    STU *head = NULL, *p = NULL;

    len--;

    while (len >= 0)
    {
        p       = (STU *)malloc(LEN);
        p->id   = data[len];
        p->next = head;
        head    = p;

        len--;
    }

    return head;
}

STU *create_Linkedlist_EXT_Circular(int data[], int len)
{
    STU *head = NULL, *p = NULL, **tmp = NULL;

    len--;
    int sum = 0;

    while (len >= 0)
    {
        p       = (STU *)malloc(LEN);
        p->id   = data[len];
        p->next = head;
        head    = p;
        if (sum-- == 0)
        {
            tmp = &(p->next);
        }

        len--;
    }
    *tmp = head;

    return head;
}

int Has_Circular(STU *head)
{
    STU **p, **p1 = NULL;

    for (p = &head; ; p = &(*p)->next)
    {
        if (p == NULL)
        {
            return 0;
        }

        for (p1 = &head; *p1 != p; p1 = &(*p1)->next)
        {
            if ((*p)->next == *p1)
            {
                return 1;
            }
        }
    }

//	return 0;	//has NOT circular!
}

STU *Has_Circular_EXT(STU *head)
{
    STU *p, *prev = NULL;

    for (p = head; ; p = p->next)
    {
        if (p == NULL)
        {
            return NULL;
        }

        for (prev = head; prev != p; prev = prev->next)
        {
            if (p->next == prev)
            {
                return p->next;
            }
        }
    }

//	return head;
}

void insert_Linkedlist_Behind(STU *head, int target, int newId)
{
    STU *newNode = NULL;

    while ((head != NULL) && (head->id != target))
    {
        head = head->next;
    }

    STU *tmp = head->next;

    newNode       = (STU *)malloc(LEN);
    newNode->id   = newId;
    head->next    = newNode;
    newNode->next = tmp;
}

void insert_Linkedlist_Front(STU **head, int target, int newId)
{
    STU **p = head, *newNode = NULL;

    while ((*p != NULL) && ((*p)->id != target))
    {
        p = &(*p)->next;
    }

    STU *tmp = *p;
    newNode       = (STU *)malloc(LEN);
    newNode->id   = newId;
    *p            = newNode;
    newNode->next = tmp;
}

void del_Node(STU **head, int target)
{
    STU **p = head;

    while (*p && (*p)->id != target)
    {
        p = &(*p)->next;
    }

    if (*p == NULL)
    {
        printf("Cannot find the node!\n");
        return;
    }

    STU *tmp = *p;
    *p  = (*p)->next;
    tmp = NULL;
    free(tmp);
}

void showme(STU *head)
{
    while (head)
    {
        printf("%d\t", head->id);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int data[] = { 10, 222, 13, 14, 5, 6 };
    int len    = sizeof(data) / sizeof(data[0]);
    STU *head  = NULL;

    head = create_Linkedlist(data, len);
    showme(head);

    insert_Linkedlist_Behind(head, 6, 666);
    showme(head);

    insert_Linkedlist_Front(&head, 10, 9999);
    showme(head);

    del_Node(&head, 666);
    showme(head);

//	head = create_Linkedlist_Circular(data, len);
//	showme(head);

//	head = create_Linkedlist_EXT_Circular(data, len);
//	showme(head);

//	int flag = Has_Circular(head);
//	printf("flag = %d\n", flag);

//	STU *Circular = Has_Circular_EXT(head);
//	printf("Circular Node is: %d\n", Circular->id);

    return 0;
}

#elif defined Demo_semaphore
//semaphore usage
int   glob = 0;
sem_t mutex1;
sem_t mutex2;

void function1(void)
{
    int count1 = 0;

    while (count1++ < 100)
    {
        sem_wait(&mutex1);              //if(mutex1 > 0), sem_wait() will return immediately, mutex1--;
        //if(mutex1 == 0), sem_wait() will block!
        glob++;
        my_trace(BRIGHT, RED, BLACK, "- 1: %4d\t", glob);

        sem_post(&mutex2);
    }
}

void function2(void)
{
    int count1 = 0;

    while (count1++ < 100)
    {
        sem_wait(&mutex2);
        glob++;
        my_trace(BRIGHT, GREEN, BLACK, "- 2: %4d\n", glob);
        sem_post(&mutex1);
    }
}

int main(void)
{
    int       rc1, rc2;
    pthread_t thread1, thread2;

    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 0);

    if (rc1 = pthread_create(&thread1, NULL, &function1, NULL))
    {
        printf("Thread creation failed: %d\n", rc1);
    }

    if (rc2 = pthread_create(&thread2, NULL, &function2, NULL))
    {
        printf("Thread creation failed: %d\n", rc2);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

#elif defined Demos_ArraysStrings
typedef struct stu
{
    int        id;
    struct stu *next;
}STU;

int Has_Circular(STU *head)
{
    STU **p, **pre;

    for (p = &head; ; p = &((*p)->next))
    {
        if (*p == NULL)
        {
            return 0;
        }

        for (pre = &head; pre != p; pre = (&(*pre)->next))
        {
            if (*pre == *p)
            {
                return 1;
            }
        }
    }
}

int Is_unique(char *str)
{
    assert(str != NULL);

    int i, j;

    for (i = 0; *(str + i) != '\0'; i++)
    {
        for (j = i + 1; *(str + j) != '\0'; j++)
        {
            if (*(str + i) == *(str + j))
            {
                return 0;                       //not unique
            }
        }
    }

    return 1;           //unique
}

char *mystrstr(char *str, char *substr)
{
    assert((str != NULL) && (substr != NULL));
    char *p = NULL, *tmp = NULL;

    for ( ; *str != '\0'; str++)
    {
        tmp = str;
        for (p = substr; *p != '\0'; p++)
        {
            if (*tmp++ != *p)
            {
                break;
            }
        }

        if (*p == '\0')
        {
            return str;
        }
    }

    return NULL;
}

void myReverse(char *str)
{
    char *end = str;
    char tmp;

    if (str)
    {
        while (*end)
        {
            end++;
        }
        end--;
        while (str < end)
        {
            tmp    = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
}


// remove the duplicate characters in a string without using any additional buffer.
void removeDup(char *str)
{
    int i;
    int j;

    for (i = 0; i < strlen(str) - 1; i++)
    {
        printf("hhhhhhhhhh\n");
        for (j = i + 1; j < strlen(str); j++)
        {
            if (*(str + i) == *(str + j))
            {
                memmove(str + j, str + j + 1, strlen(str + j + 1) + 1);
                j--;
            }
        }
    }
}

void removeDup_ext(char *str)
{
    int i, j, tail = 1;
    int len = strlen(str);

    if (len < 2)
    {
        return;
    }

    for (i = 1; i < len; i++)
    {
        printf("kkkkkkkkk\n");
        for (j = 0; j < tail; j++)
        {
            if (str[i] == str[j])
            {
                break;
            }
        }

        if (j == tail)
        {
            str[tail++] = str[i];
        }
    }

    str[tail] = '\0';
}



int main(void)
{
    char str[]   = "gooday";
    char *substr = "da";

    printf("%p\n", str);
//	printf("%c\n", *str++);
    *str = 'x';
//	printf("%c\n", *str++);



//	char *ret = mystrstr(str, substr);
//	printf("%s\n", ret);

//	int ret = Is_unique(str);
//	printf("%d\n", ret);

//	myReverse(str);
//	printf("%s\n", str);
}

#elif defined sorting_02
void insertion_sort(int arr[], int len)
{
    int i, j, tmp;

    for (i = 1; i < len; i++)
    {
        tmp = arr[i];
        j   = i - 1;

        for ( ; j >= 0 && arr[j] > tmp; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}

int main(void)
{
    int arr[] = { 1, 5, 221, 8, 0, 32, 322, 8 };

    insertion_sort(arr, sizeof(arr) / sizeof(arr[0]));

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

#elif defined d_09
int Is_SubStr(const char *s, const char *sub)
{
    assert(s != NULL && sub != NULL);
    if (strlen(sub) > strlen(s))
    {
        return 0;
    }

    const char *tmp = NULL, *p = NULL;

    for ( ; *s != '\0'; s++)
    {
        tmp = s;
        for (p = sub; *p != '\0'; p++)
        {
            if (*tmp == *p)
            {
                tmp++;
            }
            else
            {
                break;
            }
        }
        if (*p == '\0')
        {
            return 1;
        }
    }

    return 0;
}


int main(void)
{
    char *s   = "gooday!";
    char *sub = "dayq";
    int  i    = Is_SubStr(s, sub);

    printf("i = %d\n", i);
    return 0;
}

#elif defined d_07
#define TRUE     1
#define FALSE    0
int Is_Palindrome(char *s)
{
    assert(s);
    int len = strlen(s);
    int i   = 0;

    for (i = 0; i < (len + 1) / 2; i++)
    {
        if (*(s + i) != *(s + len - 1 - i))
        {
            return FALSE;
        }
    }
    return TRUE;
}

int main(void)
{
    char *s = "s1s";    //"01140t04110";//"are you ok?";

    int  flag = Is_Palindrome(s);

    printf("flag = %d\n", flag);

    return 0;
}


#elif defined d_08
typedef struct stu
{
    int        num;
    struct stu *next;
}STU;

#define LEN    sizeof(STU)

STU *create_Linklist(int data[], int number)
{
    int i;
    STU *head = NULL, *p = NULL;

    while (number-- != 0)
    {
        p       = (STU *)malloc(LEN);
        p->num  = data[number];
        p->next = head;
        head    = p;
    }

    return head;
}

void insert_linklist_tail(STU **head, int len, int num)
{
    STU **p = head, *newNode;
    int i = 0;

    while ((*head != NULL) && (*p != NULL))
    {
        p = &((*p)->next);
    }

    for (i = 0; i < len; i++)
    {
        newNode      = (STU *)malloc(LEN);
        newNode->num = num;

        *p      = newNode;
        newNode = newNode->next;
        p       = &((*p)->next);
    }
    newNode = NULL;
}

STU *sum_Linklist(STU *l1, STU *l2)
{
    assert(l1 && l2);

    STU *ret = NULL, *p = NULL, *p1 = NULL, *tmp = NULL;
    int len_l1 = 1, len_l2 = 1, len_ret = 0, flag = 0;

    tmp = l1;
    while (tmp->next != NULL)
    {
        len_l1++;
        tmp = tmp->next;
    }

    tmp = l2;
    while (tmp->next != NULL)
    {
        len_l2++;
        tmp = tmp->next;
    }

    len_ret = (len_l1 >= len_l2 ? len_l1 : len_l2);

    if (len_l1 < len_l2)
    {
        insert_linklist_tail(&l1, len_ret - len_l1, 0);
    }
    else
    {
        insert_linklist_tail(&l2, len_ret - len_l2, 0);
    }

    for (int i = 0; i < len_ret; i++)
    {
        if (i == 0)
        {
            p = p1 = ret = (STU *)malloc(LEN);

            ret->num = l1->num + l2->num;

            if (ret->num >= 10)
            {
                ret->num -= 10;
                flag      = 1;
            }
        }
        else
        {
            p = (STU *)malloc(LEN);

            p->num = l1->num + l2->num + flag;
            if (p->num >= 10)
            {
                p->num -= 10;
                flag    = 1;
            }
            else
            {
                flag = 0;
            }
            p1->next = p;
            p1       = p;
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    if (flag == 1)
    {
        p        = (STU *)malloc(LEN);
        p->num   = 1;
        p1->next = p;

        p->next = NULL;
    }

    return ret;
}

void showme(STU *head)
{
    while (head != NULL)
    {
        printf("%d\t", head->num);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int data[][5] = { { 1, 8, 4, 8, 5, 9 }, { 9, 3, 9, 9 } };
    int len       = sizeof(data[0]) / sizeof(data[0][0]);

    STU *l1 = create_Linklist(data[0], 6);
    STU *l2 = create_Linklist(data[1], 4);

    showme(l1);
    showme(l2);
    STU *new = sum_Linklist(l1, l2);

    showme(new);

    return 0;
}

#elif defined test_3

typedef struct stu
{
    int        id;
    char       *name;
    struct stu *next;
}STU;

#define LEN    sizeof(STU)

STU *creat_Linklist(int *data, int len)
{
    STU *head = NULL;
    STU *p    = NULL;

    while (len--)
    {
        p = (STU *)malloc(LEN);
//		assert(p);
        if (!p)
        {
            perror("malloc failed!");
        }
        p->id   = *(data + len);
        p->next = head;
        head    = p;
    }

    return head;
}

void del_Linklist(STU **head, int id)
{
    STU **p = head;

    while ((*p != NULL) && ((*p)->id != id))
    {
        p = &((*p)->next);
    }
//	printf("cannot find it\n");

    if (*p == NULL)
    {
        printf("Cannot find it!\n");
        return;
    }

    STU *tmp = *p;
    *p = (*p)->next;
    free(tmp);
    tmp = NULL;
}

void ins_Linklist_Front(STU **head, int id, int new_id)
{
    STU **p = head;

    while ((*p != NULL) && ((*p)->id != id))
    {
        p = &(*p)->next;
    }

    if (*p == NULL)
    {
        printf("Cannot find it!\n");
        return;
    }

    STU *tmp = *p;
    *p         = (STU *)malloc(LEN);
    (*p)->id   = new_id;
    (*p)->next = tmp;
}

void ins_Linklist_Behind(STU **head, int id, int new_id)
{
    STU **p = head;

    while (((*p) != NULL) && ((*p)->id != id))
    {
        p = &((*p)->next);
    }

    if ((*p) == NULL)
    {
        printf("Cannot find it!\n");
        return;
    }

    STU *tmp = (STU *)malloc(LEN);
    tmp->id    = new_id;
    tmp->next  = (*p)->next;
    (*p)->next = tmp;
}

void showme(STU *head)
{
    while (head)
    {
        printf("id = %d\t", head->id);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    int data[] = { 510, 111, 123, 234, 98 };
    int len    = (int)(sizeof(data) / sizeof(data[0]));
    STU *head  = NULL;

    head = creat_Linklist(data, len);
    showme(head);
    printf("\n");

    del_Linklist(&head, 2314);
    del_Linklist(&head, 111);
    showme(head);

    ins_Linklist_Front(&head, 510, 999);
    showme(head);

    ins_Linklist_Behind(&head, 510, 1999);
    showme(head);

    return(0);
}


#elif defined test_2

void print_buf(char *buf, size_t len)
{
    int k;

    printf("%02X", buf[0]);
    for (k = 1; k < len; k++)
    {
        printf(" %02X", buf[k]);
    }
}

int main(void)
{
    char buf[3] = { 1, 1, 1 };
    char *r;

    printf("Enter CTRL+D: ");
    fflush(stdout);
    r = fgets(buf, sizeof buf, stdin);
    printf("\nfgets returned %p, buf has [", (void *)r);
    print_buf(buf, sizeof buf);
    printf("]\n");

    return 0;
}

#elif defined d_04      //

char findit(char *str1, char *str2)
{
    char tmp[strlen(str2)];    // = NULL;
    int  i;

    memset(tmp, 0, strlen(str2));
    strcpy(tmp, str2);

    for ( ; *str1 != '\0'; str1++)
    {
        for (i = 0; i < strlen(tmp); i++)
        {
            if (*str1 == tmp[i])
            {
                memmove(tmp + i, tmp + i + 1, strlen(tmp + i + 1) + 1; //the number of moving is "strlen(tmp) - i"
                break;
            }
        }
    }
    return tmp[0];
}

char find_The_Extra_Char(char *str1, char *str2)
{
    int  len  = strlen(str2);
    char *tmp = (char *)malloc(len);

    memset(tmp, 0, len);
    strcpy(tmp, str2);
    char *p = tmp;

    for ( ; *str1 != '\0'; str1++)
    {
        for ( ; *tmp != '\0'; tmp++)
        {
            if (*str1 == *tmp)
            {
                printf("%c\n", *tmp);
                memmove(tmp, tmp + 1, strlen(tmp + 1) + 1);
                break;
            }
        }
    }
    return *p;
}

int main(void)
{
    /*   char *str1 = (char *)malloc(20);
     *
     * strcpy(str1, "abcdea");
     *
     * char *str2 = (char *)malloc(20);
     * strcpy(str2, "eacdbae");
     *
     * char x = findit(str1, str2);
     * printf("x = %c\n", x);
     */
//========
    char *str1 = "abcdea";
    char *str2 = "eacdbae";
//	char x = findit(str1, str2);
//    printf("x = %c\n", x);
    char x = find_The_Extra_Char(str1, str2);

    printf("x = %c\n", x);

    return 0;
}


#elif defined d_03

int main(void)
{
    number |= 1 << x;                   //set bit x
    number &= ~(1 << x);                //clear bit x
    number ^= 1 << x;                   //toggling bit x   (XOR)
    bit     = (number >> x) & 1;        //checking a bit -- this will put the value of bit x into the variable bit.
    number ^= (-x ^ number) & (1 << n); //bit n will be set if x is 1, and cleared if x is 0.

    return 0;
}

#elif defined d_02

char *
mystrstr5(const char *s1, const char *s2)
{
    const char   *p  = s1;
    const size_t len = strlen(s2);

    for ( ; (p = strchr(p, *s2)) != 0; p++)
    {
        if (strncmp(p, s2, len) == 0)
        {
            return (char *)p;
        }
    }
    return (char *)(0);
}

char *mystrstr4(string, substring)
register char *string;          /* String to search. */
char *substring;                /* Substring to try to find in string. */
{
    register char *a, *b;

    /* First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */

    b = substring;
    if (*b == 0)
    {
        return string;
    }
    for ( ; *string != 0; string += 1)
    {
        if (*string != *b)
        {
            continue;
        }
        a = string;
        while (1)
        {
            if (*b == 0)
            {
                return string;
            }
            if (*a++ != *b++)
            {
                break;
            }
        }
        b = substring;
    }
    return NULL;
}

char *strstr_6(char *str, char *substr)
{
    while (*str)
    {
        char *Begin   = str;
        char *pattern = substr;

        // If first character of sub string match, check for whole string
        while (*str && *pattern && *str == *pattern)
        {
            str++;
            pattern++;
        }
        // If complete sub string match, return starting address
        if (!*pattern)
        {
            return Begin;
        }

        str = Begin + 1;                // Increament main string
    }

    char *ret = "(null)";
    return ret;
}

char *my_strstr1(const char *haystack, const char *needle)
{
    assert(haystack && needle);

    const char *p_h = haystack;
    const char *p_n = needle;

    int        Len_h = strlen(haystack);
    int        Len_n = strlen(needle);
    int        i = 0, j = 0;

    for (i = 0; i < (Len_h - Len_n); i++)
    {
        int tmp = i;

        for (j = 0; j < Len_n; j++)
        {
            if (*(p_h + tmp++) != *(p_n + j))
            {
                break;
            }
        }
        if (j == strlen(needle))
        {
            return (char *)(p_h + i);
        }
    }

    char *p = "(null)";

    return p;
}

char *my_strstr2(const char *haystack, const char *needle)
{
    assert(haystack && needle);

    const char *p_h, *p_n;

    for ( ; *haystack != '\0'; haystack++)
    {
        p_h = haystack;

        for (p_n = needle; *p_n != '\0'; p_n++)
        {
//			printf("p_h = %s\tp_n = %s\n", p_h, p_n);

            if (*p_h++ != *p_n)
            {
                break;
            }
        }

        if (*p_n == '\0')
        {
            return (char *)haystack;
        }
    }
//    char *ret = "(null)";

    return NULL;
}

char *my_strstr3(const char *s1, const char *s2)
{
    assert(s1 && s2);

    const char *str = s1;

    for ( ; strchr(str, *s2) != NULL; str++)
    {
        if (strncmp(str, s2, strlen(s2)) == 0)
        {
            return (char *)str;
        }
    }

    char *p = "(null)";
    return p;
}

int main(void)
{
#if 1
    const char *p1 = "htt p://dd. ae";
    const char *p2 = "tx p";    //"/dd. a";

    char       *x = my_strstr2(p1, p2);

    char       *p = strstr(p1, p2);


    printf("x = %s\n", p);
#else
//step2: use array[]



    const char haystack[20] = "TutorialsPoint";
    const char needle[10]   = "Poddint";
    char       *ret;

    ret = strstr(haystack, needle);

    printf("The substring is: %s\n", ret);
#endif

    return 0;
}

#elif defined w_01                                      // strcpy string, before malloc
int main(void)
{
    char *p1 = "happy";

    strcpy(p1, "showmethe");                    //wrong	"happy" in static/initialized zone, it cannot be changed!
    printf("%s\n", p1);

    char text[] = "This is a list of lists";            //right
    strcpy(text, "good");
    printf("%s\n", text);

    return 0;
}
#elif defined d_05

typedef struct stu
{
    int        id;
    char       *name;
    struct stu *next;
} STU;

#define LEN    sizeof(struct stu)

STU *create_Linklist(int data[], int number)
{
    STU *head = NULL, *p = NULL;

    for (int i = number; i >= 0; i--)
    {
        p       = (STU *)malloc(LEN);
        p->id   = data[i];
        p->next = head;
        head    = p;
    }

    return head;
}

void ins_Linklist_Front(STU **head, int id, int new_id)
{
    STU **p = head;

    while (*p && ((*p)->id != id))
    {
        p = &((*p)->next);
    }

    STU *tmp = *p;
    *p         = (STU *)malloc(LEN);
    (*p)->id   = new_id;
    (*p)->next = tmp;
}

void ins_Linklist_Behind(STU **head, int id, int new_id)
{
    STU **p = head;

    while (*p && ((*p)->id != id))
    {
        p = &((*p)->next);
    }

    STU *tmp = (*p)->next;
    (*p)->next       = (STU *)malloc(LEN);
    (*p)->next->id   = new_id;
    (*p)->next->next = tmp;
}

void del_Linklist(STU **head, int id)
{
    STU **p = head;

    while (*p && (*p)->id != id)
    {
        p = &((*p)->next);
    }

    STU *tmp = *p;
    *p = tmp->next;
    free(tmp);
    tmp->next = NULL;
}

void swap(int *p1, int *p2)
{
    int tmp = 0;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


void bubleSort_Linklist(STU *head)
{
    int length = 0;
    int i, j;
    STU *p = head;

    while (p != NULL)
    {
        length++;
        p = p->next;
    }

    p = head;

    for (i = 0; i < length; i++)
    {
        p = head;
        while (p->next != NULL)
        {
            if (p->id > p->next->id)
            {
                swap(&(p->id), &(p->next->id));
            }
            p = p->next;
        }
    }
}

void showme(STU *head)
{
    while (head)
    {
        printf("%d\t", head->id);
        head = head->next;
    }

    printf("\n");
}

int main(void)
{
    int data[] = { 102, 45, 876, 8, 21 };
    int number = sizeof(data) / sizeof(data[0]) - 1;
    STU *head  = create_Linklist(data, number);

//	ins_Linklist_Front(&head, 8, 1000);

    ins_Linklist_Front(&head, 102, 7666);
    showme(head);

    ins_Linklist_Behind(&head, 21, 22222);
    showme(head);

    del_Linklist(&head, 21);
    showme(head);

    del_Linklist(&head, 7666);
    showme(head);

    del_Linklist(&head, 22222);
    showme(head);

    bubleSort_Linklist(head);
    showme(head);
    return 0;
}
#elif defined d_06      //fast sorting

void swap(int *p1, int *p2)
{
    int tmp;

    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void fastsorting(int arr[], int start, int end)
{
    int left, right;

    if (start < end)
    {
        left  = start + 1;
        right = end;

        while (left <= right)
        {
            while (arr[left] <= arr[start])
            {
                left++;
            }

            while (arr[right] > arr[start])
            {
                right--;
            }

            if (left < right)
            {
                swap(&arr[left], &arr[right]);
            }
        }
        swap(&arr[start], &arr[right]);

        fastsorting(arr, start, right - 1);
        fastsorting(arr, right + 1, end);
    }
}

void showme(int *arr, int length)
{
    int i;

    for (i = 0; i < length; i++)
    {
        printf("%d\t", *(arr + i));
    }
    printf("\n");
}

int main(void)
{
    int arr[]  = { 22, 112, 763, 98, 766 };
    int length = sizeof(arr) / sizeof(arr[0]);

    fastsorting(arr, 0, length - 1);
    showme(arr, length);

    return 0;
}

#elif defined w_02                                      // strncpy, pointer cross-border
int main(void)
{
    char *str = (char *)malloc(100);

    assert(str);

    strcpy(str, "showmethe");
    printf("%s\n", str);

    strcpy(str, "ab");
    printf("%s\n", str);

    strncpy(str, "NMK", 3);                     //wrong
    printf("%s\n", str);
}

#elif defined w_05

int main(void)
{
    char *str = "gqday";        //strings store in RO data zone.

    *str = 'x';
    printf("%c\n", *str++);

    return 0;
}

#elif defined d_01                                      //show strcpy, strncpy, strstr
int main(void)
{
    char *p1 = (char *)malloc(100);

    assert(p1);

    strcpy(p1, "showmethe");                    //strcpy
    printf("%s\n", p1);
    strcpy(p1, "dd");
    printf("%s\n", p1);


    strncpy(p1, "NMk", 2);                      //strncpy
    printf("%s\n", p1);

    strncpy(p1, "NMk", 3);                      //wrong code
    printf("%s\n", p1);

    char *p2   = "gooday";                      //strstr
    char *find = "da";
    char *pos  = NULL;
    pos = strstr(p2, find);
    printf("%s\n", pos);

    return 0;
}

#elif defined w_04

typedef struct stu
{
    int        id;
    struct stu *next;
}STU;

#define LEN    sizeof(STU)

STU *creat_Linklist(int data[], int num)
{
    STU *head = NULL, *p = NULL;

//	num--;

    while (--num >= 0)
    {
        p       = (STU *)malloc(LEN);
        p->id   = data[num];
        p->next = head;
        head    = p;
    }

    return head;
}

void swap(int *x, int *y)
{
    int tmp;

    tmp = *x;
    *x  = *y;
    *y  = tmp;
}

void sort_Linklist(STU *head)
{
    STU *p = head, *p1 = head->next;

    for ( ; p != NULL; p = p->next)
    {
        for ( ; p1 != NULL; p1 = p1->next)                      //wrong! the p won't get updated after every loop!
        {
            for (p1 = p->next; p1 != NULL; p1 = p1->next)       //should like this!
            {
                if ((p->id) > (p1->id))
                {
                    swap(&(p->id), &(p1->id));
                }
            }
        }
    }
}

void showme(STU *head)
{
    while (head)
    {
        printf("%d\t", head->id);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    int data[5] = { 11, 534, 0, 877, 1 };
    STU *head   = creat_Linklist(data, 5);

    showme(head);

    sort_Linklist(head);
    showme(head);

    return 0;
}

#endif
