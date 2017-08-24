
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "math.h"

#include <stdbool.h>
//#include "color.h"


/*************************
*		wrong cases
*************************/
//#define w_01	//wrong case NO.01		strcpy before malloc
//#define w_02	//wrong case NO.02		strncpy pointer cross-border
//#define w_03	//wrong case NO.03		try to get the length of a interger pointer array.

/*************************
*		demo
*************************/
//#define d_01	//show the usage of strcpy and strncpy
//#define d_02	//find and return the substring
//#define d_03	//bit operations
//#define d_04	//find the addtional charater
//#define d_05	//linklist and sorting
//#define d_06	//quick sorting

#define test_pre
//#define test
//#define test_2
//#define test_3


void print_trace()
{
//    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

#ifdef test_pre
float grades_average(float grades[7]);

int main(void)
{
	int *data[5] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	create_Linklist(data[0],int number);

    return 0;
}

float grades_average(float grades[7])
{
    int   i;
    float sum     = 0;
    float average = 0.0;

    /* calculate the sum of grades using for loop*/

    /*Changed here to <7 because i takes 0,1,2,3,4,5,6 which are 7 elements, your code is <=7 which takes 0.......7 which are 8 elements */
    for (i = 0; i < 7; i++)
    {
        /*Changed here to i from 7, your code everytime sums out of bound element, Garbage value since grades[7] does not exist*/
        sum = sum + grades[i];
    }
    average = sum / 7.f;

    return average;
}

#elif defined test
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

//	printf("len = %d\n", len);

    while ((*head != NULL) && (*p != NULL))
    {
//		printf("(*p)->num = %d\n", (*p)->num);

        p = &((*p)->next);
    }

    for (i = 0; i < len; i++)
    {
        newNode      = (STU *)malloc(LEN);
        newNode->num = num;
//		printf("xx = %d\n", newNode->num);

        *p      = newNode;
        newNode = newNode->next;
//		p = &newNode;
        p = &((*p)->next);
    }
    newNode = NULL;
//	printf("len = %d\n", len);
//	showme(*head);
}

STU *sum_Linklist(STU *l1, STU *l2)
{
    assert(l1 || l2);

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
//	int data2[] = {1, 66, 987, 7};
    int len = sizeof(data[0]) / sizeof(data[0][0]);
//	printf("%d\n", sizeof(data[0]) / sizeof(data[0][0]));

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
                memmove(tmp + i, tmp + i + 1, strlen(str2));
                break;
            }
        }
    }
    return tmp[0];
}

int main(void)
{
    char *str1 = (char *)malloc(20);

    strcpy(str1, "abcdea");

    char *str2 = (char *)malloc(20);
    strcpy(str2, "eacdbae");

    char x = findit(str1, str2);
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
        fastsorting(arr, right, end);
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

#endif
