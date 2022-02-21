
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
    char       *name;
    struct stu *next;
}STU, *STU_EXT;

#define LEN    sizeof(STU)


STU *Create_Linklist(int *array, char *name)
{
    STU *head = NULL, *p = NULL;
    int i = 0;

    for (i = 4; i >= 0; i--)
    {
        p = (STU *)malloc(LEN);
        memset(p, 0, LEN);
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

    while (*p && (*p)->score != target)         // *p must be put at first
    //while ((*p)->score != target) && *p)      // This line will cause crash. because p maybe point to NULL, then (*p)->sccore is invalid, will cause core dump.
    {
        p = &(*p)->next;
    }

    if (!*p)
    {
        my_trace(BLINK, RED, BLACK, "Cannot find the target!\n");
    }
    else
    {
        newNode = (STU *)malloc(LEN);
        memset(newNode, 0, LEN);
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
        newNode = (STU *)malloc(LEN);
        memset(newNode, 0, LEN);
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


int main()
{
    int array1[5] = { 7, 15, 72, 88, 98 };
    int array2[5] = { 2, 43, 88, 90, 1008 };

    int *array[2] = { NULL };

    array[0] = array1;
    array[1] = array2;

    int array_Data[2][5] = { { 76, 15, 72, 88, 98 }, { 442, 43, 88, 90, 1008 } };
    int (*array_ext)[5] = array_Data;


    //============usage of char *str[]===================================
    char *name[5] = { "1234", "5678", "Shaw", "Alex", "Joe" };     //the end of string will follow with '\0'
    printf("%s\t", name[0]);
    printf("%s\n", name[1]);

    //============usage of char (*str)[]=================================
    char data[][4] = { "abc", "def", "ghi" };     //the end of string will follow with '\0'
    char (*name2)[4] = NULL;
    name2            = &data[0];
    printf("%s\t", *name2);
    printf("%s\n", *(name2 + 1));
    for (int i = 0; i < 4; i++)
    {
        printf("%c\t", *(*name2 + i));
        printf("%c\n", *(*(name2 + 1) + i));
    }
	//===============================end=================================

    STU *test = (STU *)malloc(LEN);
    memset(test, 0, LEN);

    STU *test2 = (STU *)malloc(LEN);
    memset(test2, 0, LEN);

    STU *headTest = test;
    headTest->score = 8888;
    headTest->next  = test2;

    assert(headTest);

//	my_trace(BRIGHT, RED, BLACK, "test address:\t%p\n", &test);
//	my_trace(BRIGHT, GREEN, BLACK, "headTest address:\t%p\n", &headTest);
//	my_trace(BRIGHT, RED, BLACK, "headTest->next value:\t%p\n", headTest->next);

    free(headTest);
    memset(headTest, 0, LEN);

//	my_trace(BRIGHT, GREEN, BLACK, "headTest address:\t%p\n", &headTest);
//	my_trace(BRIGHT, RED, BLACK, "headTest->next value:\t%p\n\n", headTest->next);



//	STU *head1 = Create_Linklist(array[0]);
    STU *head1 = Create_Linklist(*array_ext, *name);
    showme(head1);

//	STU *head2 = Create_Linklist(array[1]);
    STU *head2 = Create_Linklist(*(array_ext + 1), *(name + 1));
    showme(head2);

#if 0
    Insert_Linklist_Front(&head1, 88, 79);
    showme(head1);

    Insert_Linklist_Behind(&head1, 7, 9);
    showme(head1);

    Insert_Linklist_Behind(&head1, 98, 38888);
    showme(head1);

    Delete_Linklist(&head1, 38888);
    showme(head1);

    sorting_Bubble(head1);
    showme(head1);

    head1 = Merge_Linklist(head1, head2);
    showme(head1);
#endif

    Merge_Linklist_EXT(&head1, &head2);
    showme(head1);
    return 0;
}
