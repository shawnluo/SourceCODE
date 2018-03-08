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
#include <errno.h>

//#define a_01	//Linked list
//#define a_02	//bubblesorting
				//quicksorting
//#define a_03	//string sorting

#define test

#if defined test

#define MYFIFO "myfifo"
#define BUFFER_SIZE 3
#define UNIT_SIZE 5
#define RUN_TIME 30
#define DELAY_TIME_LEVELS 5.0

void *producer(void *arg);
void *customer(void *arg);

int fd;
time_t end_time;
sem_t mutex,full,avail;

int main()
{
	int ret;
	pthread_t thrd_prd_id,thrd_cst_id;

	srand(time(NULL));
	end_time = time(NULL) + RUN_TIME;

        /*创建有名管道*/
	if((mkfifo(MYFIFO,0644) < 0) && (errno != EEXIST))
	{
		perror("mkfifo error!");
		exit(-1);
	}

        /*打开管道*/
	fd = open(MYFIFO,O_RDWR);
	if(fd == -1)
	{
		perror("open fifo error");
		exit(-1);
	}

        /*初始化互斥信号量为1*/
	ret = sem_init(&mutex,0,1);
        /*初始化avail信号量为 N */
	ret += sem_init(&avail,0,BUFFER_SIZE);
	/*初始化full信号量为0*/
	ret += sem_init(&full,0,0);

	if(ret != 0)
	{
		perror("sem_init error");
		exit(-1);
	}

        /*创建两个线程*/
	ret = pthread_create(&thrd_prd_id,NULL,producer,NULL);
	if(ret != 0)
	{
		perror("producer pthread_create error");
		exit(-1);
	}

	ret = pthread_create(&thrd_cst_id,NULL,customer,NULL);
	if(ret != 0)
	{
		perror("customer pthread_create error");
		exit(-1);
	}

	pthread_join(thrd_prd_id,NULL);
	pthread_join(thrd_cst_id,NULL);
	close(fd);
	unlink(MYFIFO);

	return 0;
}

void *producer(void *arg) //生产者线程
{
	int real_write;
	int delay_time;

	while(time(NULL) < end_time)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS/RAND_MAX/2.0) + 1;
		sleep(delay_time);

                /*P操作信号量avail和mutex*/
		sem_wait(&avail);
		sem_wait(&mutex);
		printf("\nproducer have delayed %d seconds\n",delay_time);

                /*生产者写入数据*/
		if((real_write = write(fd,"hello",UNIT_SIZE)) == -1)
		{
			if(errno == EAGAIN)
			{
				printf("The buffer is full,please wait for reading!\n");
			}
		}
		else
		{
			printf("producer writes %d bytes to the FIFO\n",real_write);		
			printf("Now,the buffer left %d spaces!\n",avail);
		}
                /*V操作信号量full 和 mutex*/
		sem_post(&full);
		sem_post(&mutex);
	}
	pthread_exit(NULL);
}

void *customer(void *arg) //消费者线程
{
	unsigned char read_buffer[UNIT_SIZE];
	int real_read;
	int delay_time;

	while(time(NULL) < end_time)
	{
		delay_time = (int)(rand() * DELAY_TIME_LEVELS/RAND_MAX/2.0) + 1;
		sleep(delay_time);

		sem_wait(&full); //P操作信号量full和mutex
		sem_wait(&mutex);
		memset(read_buffer,0,UNIT_SIZE);
		printf("\nCustomer have delayed %d seconds\n",delay_time);

		if((real_read = read(fd,read_buffer,UNIT_SIZE)) == -1)
		{
			if(errno == EAGAIN)
			{
				printf("The buffer is empty,please wait for writing!\n");
			}
		}
		else
		{
			printf("customer reads %d bytes from the FIFO\n",real_read);		
		}

		sem_post(&avail); //V操作信号量 avail 和 mutex
		sem_post(&mutex);		
	}

	pthread_exit(NULL);
}


#elif defined xxf
void swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

void Sort_Bubble(int arr[], int size)
{
	int i, j;

	for(i = 0; i < size - 1; i++)
	{
		for(j = i + 1; j < size; j++)
		{
			if(arr[i] > arr[j])	swap(&arr[i], &arr[j]);
		}
	}
}

void Sort_Selection(int arr[], int size)
{
	int i, j, Min;

	for(i = 0; i < size - 1; i++)
	{
		Min = i;

		for(j = i + 1; j < size; j++)
		{
			if(arr[j] < arr[Min])	Min = j;
		}

		if(Min != i)	swap(&arr[Min], &arr[i]);
	}
}

void Sort_Insertion(int arr[], int size)
{
	if(!arr)	return;
	
	int i, j, tmp;

	for(i = 1; i < size; i++)
	{
		tmp = arr[i];

		for(j = i; j > 0 && tmp < arr[j - 1]; j--)
		{
			arr[j] = arr[j - 1];
		}

		arr[j] = tmp;
	}
}

void Merge(int arr[], int tmp[], int L_Start, int R_Start, int R_End)
{
	if(!arr)	return;

	if(L_Start <= R_Start)
	{
		int L_End = R_Start - 1;
		int tmp_Start = L_Start;
		int tmpsize = R_End - L_Start + 1;

		while(L_Start <= L_End && R_Start <= R_End)
		{
			if(arr[L_Start] <= arr[R_Start])
			{
				tmp[tmp_Start++] = arr[L_Start++];
			}
			else
			{
				tmp[tmp_Start++] = arr[R_Start++];
			}
		}

		while(L_Start <= L_End)
		{
			tmp[tmp_Start++] = arr[L_Start++];
		}
		
		while(R_Start <= R_End)
		{
			tmp[tmp_Start++] = arr[R_Start++];
		}

		for(int i = 0; i < tmpsize; i++, R_End--)
		{
			arr[R_End] = tmp[R_End];
		}
	}		
}

void Sort_Merge(int arr[], int tmp[], int Left, int Right)
{
	if(!arr) return;
	
	if(Left < Right)
	{
		int mid = (Left + Right) / 2;

		Sort_Merge(arr, tmp, Left, mid);
		Sort_Merge(arr, tmp, mid + 1, Right);

		Merge(arr, tmp, Left, mid + 1, Right);
	}
}

int main(void)
{
	int data[] = {122, 22, 871, 0, 9};

//	int tmp[5] = {0};	//tmp数组要指定长度为>=5，否则算法不正确
//	Sort_Merge(data, tmp, 0, 4);

//	Sort_Insertion(data, sizeof(data) / sizeof(data[0]));

//	Sort_Bubble(data, 5);
	Sort_Selection(data, 5);

	for(int i = 0; i < 5; i++)
	{
		printf("%d\t", data[i]);
	}
	printf("\n");
	
	return 0;
}

#elif defined xx

int Is_Anagrams(char *str1, char *str2)
{
	assert(str1 && str2);

	int arr[255];
	memset(arr, 0, sizeof(arr));

	char *p = str1;
	while(*p)
	{
		arr[*p]++;
		p++;
	}

	p = str2;

	while(*p)
	{
		arr[*p]--;
		p++;
	}

	for(int i = 0; i < 255; i++)
	{
		if(arr[i] != 0)
		{
			return 0;	//if there is a 1, then they're not anagrams.
		}
	}

	return 1;
}

int main(void)
{
	char *str1 = "showme";
	char *str2 = "shoemw";
	
	int ret = Is_Anagrams(str1, str2);
	printf("%d\n", ret);
}

#elif defined a_02


int *bubble_sorting(int data[], int size)
{
	int temp = 0;	

	for(int i = 0; i < size - 1; i++)  
	{  
		for(int j = i + 1; j < size; j++)  
		{  
			if(data[i] > data[j]) 
			{  
				temp = data[i];  
				data[i] = data[j];  
				data[j] = temp;  
			}  
		}  
	}
	return data;
}

int main(void)
{
	int data[] = {1, 22, 32, 12, 87, 0};

	/*
		int data[] = {1, 22, 32, 12, 87, 0};
		data = bubble_sorting(data, sizeof(data) / sizeof(data[0]));

		WRONG!!!!!
		注意！数组名是一个地址，是一个指针常量，是const型的，不能被修改！！！
	*/

	bubble_sorting(data, sizeof(data) / sizeof(data[0]));

	printf("%d\n", sizeof(data) / sizeof(data[0]));
	
	for(int i = 0; i < sizeof(data) / sizeof(data[0]); i++)
	{
		printf("%d\t", data[i]);
	}
	printf("\n");
}

#elif defined a_01

typedef struct node
{
	int id;
	struct node *next;
}Node, *pNode;

#define LEN sizeof(Node)

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

pNode create_linkedlist(int data[], int len)
{
	pNode pHead = NULL;
	pNode p = NULL;

	while(len--)
	{
		p = (pNode)malloc(LEN);
		p->id = data[len];
		p->next = pHead;
		pHead = p;
	}
	return pHead;
}

void insert_linkedlist_front(pNode *ppHead, int targetId, int newId)
{
	assert(*ppHead);

	pNode *pp = ppHead;

	while(*pp && (*pp)->id != targetId)
	{
		pp = &(*pp)->next;
	}

	if(!*pp)
	{
		printf("Cannot find it\n");
		return;
	}

	pNode newNode = (pNode)malloc(LEN);
	newNode->id = newId;
	newNode->next = *pp;
	*pp = newNode;
}

void insert_linkedlist_behind(pNode pHead, int targetId, int newId)
{
	assert(pHead);

	pNode p = pHead;

	while(p && p->id != targetId)
	{
		p = p->next;
	}

	if(!p)
	{
		printf("Cannot find it\n");
		return;
	}
	
	pNode newNode = (pNode)malloc(LEN);
	newNode->id = newId;
	newNode->next = p->next;
	p->next = newNode;
}

void del_ll(pNode *ppHead, int targetId)
{
	assert(*ppHead);
	
	pNode *pp = ppHead;

	while(*pp && (*pp)->id != targetId)
	{
		pp = &(*pp)->next;
	}

	if(!*pp)
	{
		printf("Cannot find it\n");
		return;
	}
	
	pNode tmp = *pp;
	*pp = (*pp)->next;

	free(tmp);
	tmp = NULL;
}

pNode reverse_ll(pNode pHead)
{
	assert(pHead);

	pNode p, pL, pR;
	p = pHead->next;
	pL = pHead;
	pHead->next = NULL;

	while(p)
	{
		pR = p->next;
		p->next = pL;
		pL = p;
		p = pR;
	}

	return pL;
}

void swap(int *x, int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

pNode sort_bubble_ll(pNode pHead)
{
	pNode p1 = NULL, p2 = NULL;
	int tmp;
	showme(pHead);

	for(p1 = pHead; p1->next; p1 = p1->next)
	{
		for(p2 = p1->next; p2; p2 = p2->next)
		{
			if(p1->id > p2->id)
			{
				tmp = p1->id;
				p1->id = p2->id;
				p2->id = tmp;
				//swap(&p1->id, &p2->id);
			}
		}
	}
	
	showme(pHead);
	
	return pHead;
}

pNode merge_ll(pNode pHead1, pNode pHead2)
{
	assert(pHead1 && pHead2);

	pNode p = pHead1;
	while(p->next)
	{
		p = p->next;
	}

	p->next = pHead2;

	pHead1 = sort_bubble_ll(pHead1);
	
	return pHead1;
}

int Has_Circular_LL(pNode pHead)
{
	assert(pHead);

	
}

void Create_Circular_LL(pNode pHead)
{
	assert(pHead);

	if(Has_Circular_LL(pHead))
	{
		printf("Has circular already!\n");
		return;
	}
}

int main(void)
{
	int data[][5] = {	{0, 11, 2, 3, 4},
						{5, 16, 7, 8, 9},
						{10, 11, 12, 13, 14}};
	pNode pHead = create_linkedlist(data[0], sizeof(data[0]) / sizeof(data[0][0]));
//	showme(pHead);

	pNode pHead1 = create_linkedlist(data[1], sizeof(data[1]) / sizeof(data[1][0]));

//	insert_linkedlist_behind(pHead, 2, 200);
//	showme(pHead);
	
//	insert_linkedlist_front(&pHead, 0, 100);
//	showme(pHead);

//	del_ll(&pHead, 0);
//	showme(pHead);

//	pHead = reverse_ll(pHead);
//	showme(pHead);

	pHead = merge_ll(pHead, pHead1);
//	showme(pHead);

	return 0;
}

#elif defined a_02

#endif
