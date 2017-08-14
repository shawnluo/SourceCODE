
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"

typedef struct stu
{
    int        score;
    char       *str;
    struct stu *next;
}STU, *STU_EXT;

#define LEN    sizeof(STU)


#if 0
STU *Create_Linklist(int *array)
{
    STU *head = NULL, *p = NULL;
    int i = 5;

    while (i-- > 0)
    {
        p        = (STU *)malloc(LEN);
        p->score = *(array + i);
        p->next  = head;
        head     = p;
    }

    return head;
}

void Insert_Linklist(STU **head, int number, int newNumber)
{
    STU **p = head, *newNode;

    while (*p && (*p)->score != number)
    {
        p = &(*p)->next;
    }

    newNode        = (STU *)malloc(LEN);
    newNode->score = newNumber;
    newNode->next  = *p;

    *p = newNode;
}

STU *Delete_Linklist(STU **head, int x)
{
}

STU *Merge_Linklist(STU *head1, STU *head2)
{
    return head1;
}


void showme(STU *head)
{
    while (head)
    {
        printf("%d\t", head->score);

        head = head->next;
    }
    printf("\n");
}
#endif

STU *Create_Linklist(int *array)
{
    STU *head = NULL, *p = NULL;
    int i = 0;

    for (i = 4; i >= 0; i--)
    {
        p        = (STU *)malloc(LEN);
        p->score = *(array + i);
        p->next  = head;
        head     = p;
    }

    return head;
}

void Insert_Linklist_Front(STU **head, int target, int newValue)
{
    STU **p      = head;
    STU *newNode = NULL;

    while (*p && (*p)->score != target)
    {
        p = &(*p)->next;
    }

    if (!*p)
    {
        my_trace(BLINK, RED, BLACK, "Cannot find the target!\n");
    }
    else
    {
        newNode        = (STU *)malloc(LEN);
        newNode->score = newValue;
        newNode->next  = *p;
        *p             = newNode;
    }
}

void Insert_Linklist_Behind(STU **head, int target, int newValue)
{
    STU **p = head, *newNode = NULL;

    while (*p && (*p)->score != target)
    {
        p = &(*p)->next;
    }

    if (!*p)
    {
        my_trace(BLINK, RED, BLACK, "Cannot find the target!\n");
    }
    else
    {
        newNode        = (STU *)malloc(LEN);
        newNode->score = newValue;
        newNode->next  = (*p)->next;
        (*p)->next     = newNode;
    }
}


void showme(STU *head)
{
    while (head)
    {
        my_trace(BRIGHT, GREEN, BLACK, "%d\t", head->score);
        head = head->next;
    }
    printf("\n");
}

void Delete_Linklist(STU **head, int target)
{
    STU **p = head, *deletePointer = NULL;

    while (*p && (*p)->score != target)
    {
        p = &(*p)->next;
    }

    if (!*p)
    {
        my_trace(BLINK, RED, BLACK, "Cannot find the target!\n");
    }
    else
    {
        deletePointer       = *p;
        *p                  = deletePointer->next;
        deletePointer->next = NULL;

        free(deletePointer);
        deletePointer = NULL;
    }
}


void swap(STU *p, STU *t)
{
    int tmp = p->score;

    p->score = t->score;
    t->score = tmp;
}

void sorting_Bubble(STU *head)
{
    STU *p = NULL, *t = NULL;

    for (p = head; p; p = p->next)
    {
        for (t = p->next; t; t = t->next)
        {
            if (p->score > t->score)
            {
                swap(p, t);
            }
        }
    }
}


//Way1: we merge head2 into head1
STU *Merge_Linklist(STU *head1, STU *head2)
{
    STU *p1 = NULL, *p2 = NULL;

    sorting_Bubble(head1);
    sorting_Bubble(head2);

    for (p2 = head2; p2; p2 = p2->next)
    {
        for (p1 = head1; p1; p1 = p1->next)
        {
            if (p2->score <= p1->score)
            {
                Insert_Linklist_Front(&head1, p1->score, p2->score);
                break;
            }

            if (!p1->next)
            {
                Insert_Linklist_Behind(&head1, p1->score, p2->score);
                break;
            }
        }
    }

    return head1;
}


//way2: 1. link the whole linklist head2 into the end of linklist head1.
//		2. sorting linklist head1
void Merge_Linklist_EXT(STU **head1, STU **head2)
{
    STU **p = head1;

    while (*p)
    {
        p = &(*p)->next;
    }

    *p = *head2;

    sorting_Bubble(*head1);
}

char *mystrcpy(char *des, const char *src)
{
    assert(des && src);

    char *address = des;
    while ((*des++ = *src++) != 0)
    {
        ;
    }

    return address;
}
#if 0
int main()
{
    char *str1 = "1234567890";
    char *str2 = (char *)malloc(strlen(str1) + 1);

    str2 = strcpy(str2, str1);
//	str2 = mystrcpy(str2, str1);


    my_trace(BRIGHT, GREEN, BLACK, "str2 address:\t%p\n", str2);
    my_trace(BRIGHT, GREEN, BLACK, "str2 address:\t%s\n", str2);
    my_trace(BRIGHT, GREEN, BLACK, "str2 size:\t%d\n", strlen(str2));

//	printf();

    return 0;
}
#endif

#define Row       5
#define Column    7

int main(void)
{
/**************data[N][m]******************************************
 *	the end of string will follow with '\0'
 *****************************************************************/
    char *data[Row] = { "123456", "7890pK", "Shaw", "Alex", "Joe" };
    //============END=================================


/*============usage of char *str[N]=================================
 *	1. str is a array, has N elements, every element is a pointer!
 *	2. m is the second dimension of this 2 dimensions array!
 *	3. free every name[i]
 ********************************************************************/
    char *name[Row] = { NULL };

    /******malloc way1:*****************************************************
     *      malloc for every name[i]
     ********************************/
    for (int i = 0; i < Row; i++)
    {
        name[i] = (char *)malloc(sizeof(char) * Column);
        strcpy(name[i], data[i]);
        my_trace(BRIGHT, GREEN, BLACK, "%s\t", name[i]);

        free(name[i]);
    }
    printf("\n");

    /******malloc way2:*****************************************************
     *      1. malloc once for name[Row][Column] to make the malloc area continue
     *      2. then assignment the address to every name[i]
     *      3. only need free name[0]
     *************************************/
    name[0] = (char *)malloc(sizeof(char) * Row * Column);
    for (int i = 0; i < Row; i++)
    {
        name[i + 1] = name[i] + Column;
        strcpy(name[i], data[i]);
        my_trace(BRIGHT, GREEN, BLACK, "%s\t", name[i]);
    }
    printf("\n");
    free(name[0]);
    //============END=================================


/*************usage of char (*str)[N]********************************
*
*	1. str is a pointer, points to the row of a 2 dimensions array, this row has N elements!
*	2. N is the first dimension of this 2 dimensions array!
*	3. p is the first address of this 2 dimensions array--str[][N]
*
********************************************************************/
	char (*name2)[Column] = NULL;
#if 1
	name2 = (char (*)[Column])malloc(sizeof(char) * Row * Column);
	printf("1 --- %p\n", name2);

//	name2 = data[0];	// error!!! If name2 = data[0], why did you malloc memory? 
						// And the error will occur when you free name2;
//	free(name2);		// if name2 = data[0], then segment fault will occur!
						
	for(int i = 0; i < Row; i++)
	{
		strcpy(*(name2 + i), data[i]);
	}

	printf("%s\n", *(name2 + 2));

//	printf("2 --- %p\n", name2);

//    printf("%s\n", *name2);
//    printf("%s\n", *(name2 + 1));
    for (int i = 0; i < Column; i++)
    {
        printf("%c\t", *(*name2 + i));
        printf("%c\n", *(*(name2 + 1) + i));
    }
//	printf("3 --- %p\n", name2);

#else
	for(int i = 0; i < Row; i++)
	{
//		*(name2 + i) = (char (*)[Column])malloc(sizeof(char) * Column);

//        my_trace(BLINK, GREEN, BLACK, "%s\t", name2[i]);
	}
#endif	
    //============END=================================

    return 0;
}

#if 0
#ifndef _MSG__H__
#define _MSG__H__
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BODY_LEN    1024

typedef struct _testmsg
{
    long type;
    char msgbody[1];
} testmsg, *ptestmsg;

#define MSG_TYPE    0xFF
#define MSGS_LEN    (sizeof(long) + sizeof(char) * BODY_LEN)

// 一般使用ftok函数获取key_t，这里简单起见，直接定义一个键值。
#define MSG_KEY     (key_t)0x320310F2

int open_queue()
{
// 获取queue的ID，如果不存在则创建queue。
    return msgget(MSG_KEY, IPC_CREAT);
}

#endif
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "msg.h"

void do_statistic(void);
unsigned char rcvbuf[MSGS_LEN] = { 0 };

int main(int argc, char **argv)
{
    int msqid = open_queue();

    if (msqid == -1)
    {
        printf("error when opened the queue!\n");
        return -1;
    }

    while (1)
    {
        int ret = msgrcv(msqid, rcvbuf, MSGS_LEN, MSG_TYPE, IPC_NOWAIT);
        do_statistic();
        if (ENOMSG == errno || EAGAIN == errno)
        {
            usleep(12000);
            continue;
        }

        if (ret == -1)
        {
            printf("msgrcv failed!\n");
        }

        usleep(12030);
    }

    return 0;
}

void do_statistic(void)
{
    static int msgcount = 0;

    msgcount++;
    printf("do recived msg %d times.\n", msgcount);
}
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "msg.h"

unsigned char send_msg[MSGS_LEN] = { 0 };
unsigned char *some_array[1024] = { 0 };

int main(int argc, char **argv)
{
    int msqid = open_queue();

    if (msqid == -1)
    {
        printf("error when opened the queue!\n");
        return -1;
    }

    int i = 0;
    while (1)
    {
        ptestmsg p = (ptestmsg)send_msg;
        p->type = MSG_TYPE;
        memset(p->msgbody, 0, BODY_LEN);
        int ret = msgsnd(msqid, send_msg, MSGS_LEN, 0);

        if (-1 == ret)
        {
            printf("error when sent the msg\n");
            return -1;
        }
        printf("sent %d msges.\n", ++i);
        usleep(500000);
    }

    return 0;
}
#endif
