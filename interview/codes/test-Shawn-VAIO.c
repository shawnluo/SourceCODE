
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

#include <vector>
#include <iostream>

using namespace std;

class Base
{
public:
    Base(const char* name);
    // warning! the destructor should be virtual
    ~Base();

    virtual void doStuff();
private:
    const char* m_name;
};

Base :: Base(const char* name) : m_name(name)
{

}

Base :: ~Base()
{

}



void Base :: doStuff()
{
    cout << "Doing stuff in Base" << endl;
}



class Derived : public Base
{
public:
    Derived(const char* name);
    ~Derived();

virtual void doStuff();
private:
    vector<int>* m_charCodes;
};

Derived :: Derived(const char* name) : Base(name)
{
    m_charCodes = new vector<int>;
} 

Derived :: ~Derived()
{
    delete m_charCodes;
}

void Derived :: doStuff() 
{
    cout << "Doing stuff in Derived" << endl;
}

int main(int argc, char* argv[])
{
    // assign the derived class object pointer to
    // the base class pointer
    char* theName = "Some fancy name";
    Base* b = new Derived(theName);

    // do some computations and then delete the
    // pointer
    delete b;
    return 0;
}


#elif defined xx
#include<iostream>
using namespace std;

int public_dataX;

class X
{
private:
	int private_dataX;
protected:
	int protected_dataX;
public:
	int public_dataX;
	int cc(int x);
	
	X operator+(const X &b)
	{
		X box;
		box.public_dataX= this->public_dataX + b.private_dataX;

		return box;
	}
};

int X::cc(int x)
{
	return ::public_dataX;
}

class A :public X
{
public:	
/*	int a_var;
	int add(int a);
	int add(int a, int b);*/
	void funct()
	{
		int a;
//		a = private_dataX;
		a = protected_dataX;
		a = public_dataX;
	}
};

/*
int A::add(int a)
{
	return a + ::a_var;
}

int A::add(int a, int b)
{
	return a + b;
}
*/
int main(void)
{
	int x;

	A objA;
	
	x = objA.public_dataX;
//	x = objA.private_dataX;
	
	return 0;
}

#elif defined Cplusplus

#include<iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////
class X       //parent class
{
private:
    int private_dateX;
protected:
    int protected_dateX;
public:
    int public_dateX;
};
//////////////////////////////////////////////////////////////////////////
class A :public X      //derive class B from base class A (shared inheritance)
{
public:
    void funct()
    {
        int a;
        a = private_dataX;   //error: the privated member of base class is invisible in derive class
        a = protected_dataX; //ok: the protected member of base class is protected member in derive class
        a = public_dataX;    //ok: the public member of base class is public member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
class B :private X  //derive class C from base class A(privated inheritance)
{
public:
    void funct()
    {
        int b;
        b = private_dataX;    //error: the privated member of base class is invisible in derive class 
        b = protected_dataX;  //ok: the protected member of base class is privated member in derive class
        b = public_dataX;     //ok: the public member of base class is privated member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
class C :protected X   //derive class D from base class A (protectd inheritance)
{
public:
    void funct()
    {
        int c;
        c = private_dataX;   //error: the privated member of base class is invisible in derive class
        c = protected_dataX; //ok: the protected member of base class is privated member in derive class
        c = public_dataX;    //ok: the public member of base class is protectd member in derive class
    }
};
//////////////////////////////////////////////////////////////////////////
int main()
{
    int x;
 
    A objA;
    x = objA.private_dataX;   //error: 基类中私有成员在派生类中是不可见的，对对象不可见
    x = objA.protected_dataX; //error: 基类的保护成员在派生类中为保护成员，对对象不可见
    x = objA.public_dataX;    //ok: 基类的公共成员在派生类中为公共成员，对对象可见
 
    B objB;
    x = objB.private_dataX;   //error: 基类中私有成员在派生类中是不可见的，对对象不可见
    x = objB.protected_dataX; //error: 基类的保护成员在派生类中为私有成员，对对象不可见
    x = objB.public_dataX;    //error: 基类的公共成员在派生类中为私有成员，对对象不可见
 
    C objC;
    x = objC.private_dataX;   //error: 基类中的私有成员在派生类中是不可见的，对对象不可见
    x = objC.protected_dataX; //error: 基类的保护成员在拍摄各类中是保护成员，对对象不可见
    x = objC.public_dataX;    //error: 基类的公共成员在派生类中为保护成员，对对象不可见
 
    return 0;
}


#elif defined string_demo

void showme(char *str)
{
	printf("%s\n", str);
}

void reverse_str(char *str)
{
	assert(str);

	char *pStart = str;
	char *pEnd = str + strlen(str) - 1;
	char tmp;
	
	while(pStart < pEnd)
	{
		tmp = *pStart;
		*pStart++ = *pEnd;
		*pEnd-- = tmp;
	}
}

char *Copy_Str(char *strDest, const char *strSrc)
{
	assert(strDest && strSrc);

	if(strDest == strSrc)
	{
		return strDest;
	}

	char *tmpptr = strDest;
	
	while(*strDest++ = *strSrc++)
	{
		;
	}

	return tmpptr;
}

int main(void)
{
	char *strSrc = (char *)malloc(100);
	strcpy(strSrc, "showmustgoon!");

	char *strDest = (char *)malloc(100);

	reverse_str(strSrc);
	showme(strSrc);

	showme(strDest);

	char *tmp = Copy_Str(strDest, strSrc);
	showme(tmp);
}

#elif defined sorting
void swap(int *x, int *y)
{
    int tmp;

    tmp = *x;
    *x  = *y;
    *y  = tmp;
}

void Sorting_Selection(int arr[], int num)      //selection
{
    int i, j, k;

    for (i = 0; i < num - 1; i++)
    {
        k = i;

        for (j = i + 1; j < num; j++)
        {
            if (arr[k] > arr[j])
            {
                k = j;
            }
        }
        if (k != i)
        {
            arr[k] = arr[k] ^ arr[i];
            arr[i] = arr[k] ^ arr[i];
            arr[k] = arr[k] ^ arr[i];
        }
    }
}

void Sorting_Quick(int arr[], int start, int end)
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

        Sorting_Quick(arr, 0, right - 1);
        Sorting_Quick(arr, right + 1, end);
    }
}

void showme(int arr[], int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int Partition(int L[], int K, int M)
{
    int i, j, x, t;

    x = L[M];
    i = K - 1;
    for (j = K; j <= M; j++)
    {
        if (L[j] < x)
        {
            i++;
            t    = L[j];
            L[j] = L[i];
            L[i] = t;
        }
    }
    L[M]     = L[i + 1];
    L[i + 1] = x;
    return i + 1;
}

void QuickSort(int L[], int r, int s)
{
    int q;

    if (r < s)
    {
        q = Partition(L, r, s);
        QuickSort(L, r, q - 1); 
        QuickSort(L, q + 1, s); 
    }
}


int main(void)
{
    int arr[5] = { 11, 3, 543, 22, 9 };
    int len    = sizeof(arr) / sizeof(arr[0]);

//	Sorting_Selection(arr, len);
//	showme(arr, len);

//    Sorting_Quick(arr, 0, 4);
//    showme(arr, len);

	QuickSort(arr, 0, 4);
	showme(arr, len);

    return 0;
}

#elif defined LindList
typedef struct node
{
    int         id;
    struct node *next;
}Node, *pNode;

#define LEN    sizeof(Node)

//creating from the head
pNode Create_LinkedList(int data[], int num)
{
    assert(data);

    pNode pHead = NULL, p = NULL, p1 = NULL;

    if (!pHead)
    {
        pHead       = (pNode)malloc(LEN);
        pHead->id   = data[0];
        pHead->next = NULL;

        p = p1 = pHead;
    }

    for (int i = 1; i < num; i++)
    {
        p       = (pNode)malloc(LEN);
        p->id   = data[i];
        p->next = NULL;

        p1->next = p;
        p1       = p;
    }

    return pHead;
}

//creating from the tail
pNode Create_LinkedList_Ext(int data[], int num)
{
    assert(data);

    pNode pHead = NULL, p = NULL;

    while (num--)
    {
        p       = (pNode)malloc(LEN);
        p->id   = data[num];
        p->next = pHead;

        pHead = p;
    }

    return pHead;
}

void Insert_Node_Front(pNode *pHead, int targetId, int newId)
{
    assert(*pHead);

    pNode *p = pHead;

    while (*p && (*p)->id != targetId)
    {
        p = &(*p)->next;
    }

    if (!*p)
    {
        printf("11 Cannot find it!\n");
        return;
    }

    pNode pNew = (pNode)malloc(LEN);
    pNew->id   = newId;
    pNew->next = *p;

    *p = pNew;
}

void Insert_Node_Behind(pNode pHead, int targetId, int newId)
{
    assert(pHead);

    pNode p = pHead;

    while (p && p->id != targetId)
    {
        p = p->next;
    }

    if (!p)
    {
        printf("22 Cannot find it!\n");
        return;
    }

    pNode pNew = (pNode)malloc(LEN);
    pNew->id   = newId;
    pNew->next = p->next;

    p->next = pNew;
}

void Del_Node(pNode *ppHead, int targetId)
{
    assert(*ppHead);

    pNode *pp = ppHead;

    while (*pp && (*pp)->id != targetId)
    {
        pp = &(*pp)->next;
    }

    if (!*pp)
    {
        printf("In (Del_Node) Cannot find it!\n");
        return;
    }

    pNode tmp = *pp;
    *pp = (*pp)->next;

    free(tmp);
    tmp = NULL;
}

void Del_All(pNode *ppHead)
{
    assert(*ppHead);

    int delId;

    while (*ppHead)
    {
        delId = (*ppHead)->id;
        Del_Node(ppHead, delId);
    }
}

void Del_Node_Ext(pNode *ppHead, int startNode, int num)        //head node is no.0
{
    assert(*ppHead);

    pNode *ppStart = ppHead;
    int   Length = 0, i = 0;

    //1. get the Length - length of linked list
    while (*ppStart)
    {
        Length++;
        ppStart = &(*ppStart)->next;
    }

    //2. if startNode > Length or (startNode + num) > Length, then return, else do the del.
    if ((startNode > Length - 1) || (startNode + num) > Length)
    {
        printf("Wrong start and num!\n");
        return;
    }

    ppStart = ppHead;
    int targetId;

    for (i = 0; i < startNode; i++)
    {
        ppStart = &(*ppStart)->next;
    }

    for (i = 0; i < num; i++)
    {
        targetId = (*ppStart)->id;
        Del_Node(ppHead, targetId);
    }
}

pNode Reverse_LinkedList(pNode pHead)
{
    assert(pHead);

    pNode p = pHead, pPrev = NULL, pNext = NULL;

    while (p)
    {
        pNext = p->next;

        if (p == pHead)
        {
            p->next = NULL;
        }
        else
        {
            p->next = pPrev;
        }
        pPrev = p;
        p     = pNext;
    }

    return pPrev;
}

int Has_Circular(pNode pHead)
{
    assert(pHead);

    pNode p = pHead, p2 = NULL;

    for ( ; ; p = p->next)
    {
        if (!p)
        {
            return 0;
        }

        for (p2 = pHead; p2 != p; p2 = p2->next)
        {
            if (p2->next == p->next)
            {
                return 1;
            }
        }

        if ((p->next == pHead) || (p->next == p))
        {
            return 1;
        }
    }
}

void Create_Circular(pNode pHead, int targetId)
{
    assert(pHead);

    pNode p = pHead, pTail = pHead;

    if (Has_Circular(pHead))
    {
        printf("The Linked List already has circular!\n");
        return;
    }

    while (p && p->id != targetId)
    {
        p = p->next;
    }

    if (!p)
    {
        printf("Cannot find the target id!\n");
        return;
    }

    while (pTail->next)
    {
        pTail = pTail->next;
    }

    pTail->next = p;
}

void Sorting_LinkedList(pNode pHead)    //bubble sorting by id
{
    assert(pHead);

    pNode p1 = NULL, p2 = NULL;
    int   tmp;

    for (p1 = pHead; p1 != NULL; p1 = p1->next)
    {
        for (p2 = p1->next; p2 != NULL; p2 = p2->next)
        {
            if (p1->id > p2->id)
            {
                tmp    = p1->id;
                p1->id = p2->id;
                p2->id = tmp;
            }
        }
    }
}

void Sorting_LL(pNode pHead)    //selection
{
}

pNode Merge_LinkedList(pNode list1, pNode list2)        //adding list2 on the tail of list1, then sorting
{
    assert(list1 && list2);

    pNode p = list1;

    while (p->next)
    {
        p = p->next;
    }

    p->next = list2;

    Sorting_LinkedList(list1);

    return list1;
}

pNode Merge_LL_Ext()    //comparing and inserting
{
}

void showme(pNode pHead)
{
    assert(pHead);

    while (pHead)
    {
        printf("%d\t", pHead->id);
        pHead = pHead->next;
    }
    printf("\n");
}

int main(void)
{
    //int xx[0];
    int data[3][5] = { { 10, 121,  2,  3,  4 },
                       {  5,   6,  7,  8,  9 },
                       { 10,  11, 12, 13, 14 } };
    int num = sizeof(data[0]) / sizeof(data[0][0]);

#if 0
    pNode pHead = Create_LinkedList_Ext(*data[0], num);
    showme(pHead);

    Insert_Node_Front(&pHead, 4, 333);
    showme(pHead);

    Insert_Node_Behind(pHead, 333, 444);
    showme(pHead);

    Del_Node(&pHead, 0);
    showme(pHead);
    Del_Node(&pHead, 1);
    showme(pHead);
    Del_Node(&pHead, 2);
    showme(pHead);
    Del_Node(&pHead, 3);
    showme(pHead);

    pHead = Reverse_LinkedList(pHead);
    showme(pHead);

    int ret = Has_Circular(pHead);
    printf("ret = %d\n", ret);

    Create_Circular(pHead, 0);
    showme(pHead);

    ret = Has_Circular(pHead);
    printf("ret = %d\n", ret);

    Del_Node_Ext(&pHead, 1, 2);
    showme(pHead);
    Del_All(&pHead);
    showme(pHead);
    Sorting_LinkedList(pHead);
    showme(pHead);
#endif

    pNode list1 = Create_LinkedList_Ext(data[0], num);
    showme(list1);

    pNode list2 = Create_LinkedList_Ext(data[1], num);
    showme(list2);

    list1 = Merge_LinkedList(list1, list2);     //adding list2 on the tail of list1, then sorting
    showme(list1);

    return 0;
}
#endif
