
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

void print_ext(int n)
{
    printf("n = %d\n", n);
    if(n > 0)
    {
        print_ext(n / 2);
    }
    else
    {
        return;
    }
    printf("%d ", n % 2);
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void showme(int *x, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

void test()
{
    int i, j;
    int arr[5] = {11, 3, 8, 777, -22};

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5 - i; j++)
        {
            if(arr[j] < arr[j + 1])
            {
                swap(arr + j, arr + j + 1);
            }
        }
    }

    showme(arr, 5);
}

void test_2()
{
    int i, j;
    int arr[5] = {11, 3, 8, 777, -22};

    for(i = 0; i < 5; i++)
    {
        int min = i;
        for(j = i + 1; j < 5; j++)
        {
            if(arr[j] > min)
            {
                min = j;
            }
        }
        swap(arr + i, arr + min);
    }
    showme(arr, 5);
}

int ptr = -1;
int stack[100] = {0};

void push(int data)
{
    ptr++;
    stack[ptr] = data;
}

int pop()
{
    int val = stack[ptr];
    ptr--;

    return val;
}

//1: is empty
//0: not empty
int is_empty()
{
    return ptr == -1 ? 1 : 0;
}

void print_bin(int n)
{
    int mod = 0;
    int arr[10] = {0};
    int i = 0;
    int size = 0;

    while(n > 0)
    {
        mod = n % 2;
        n = n / 2;
        push(mod);
        size++;
    }

    while(is_empty() != 1)
    {
        arr[i++] = pop();
    }

    for(i = 0; i < size; i++)
    {
        printf("%d, ", arr[i]);
    }
}

void print_bin2(int n)
{
    if(n > 0)
    {
        //n = n / 2;
        print_bin2(n / 2);
    }
    else
    {
        return;
    }
    printf("%d ", n % 2);
}

void reverse_str(void)
{
    char str[20] = "show me!";

    char *p = str;
    char *q = str + strlen(str) - 1;

    while(p < q)
    {
        char tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q--;
    }
    printf("%s\n", str);
}

void del_space()
{
    char str[200] = "sh ow me !";
    int size = strlen(str);
    int n = size;

    for(int i = 0; i < size; i++)
    {
        //printf("   %c\n", str[i]);
        if(str[i] != ' ')
        {
            str[n] = str[i];
            n++;
        }
    }
    str[n] = '\0';
    //printf("%s\n", str);
    strcpy(str, str + size);
    printf("%s\n", str);
}

void del_space_2()
{
    char str[200] = "sh ow me  !";
    int size = strlen(str);
    //int space = 0;
    int newSize = size;

    printf("%s\n", str);
/*
    int i = 0;
    while(str[i++] != '\0')
    {
        if(str[i] == ' ')
        {
            space++;
        }
    }
    printf("%d\n", space);

    newSize = size + space;
*/
    while((size - 1) >= 0)
    {
        if(str[size - 1] != ' ')
        {
            str[newSize - 1] = str[size - 1];
            size--;
            newSize--;
        }
        else
        {
            size--;
        }
    }

    printf("%s\n", str);
}


//loop find 
void insect_sorting()
{
    int arr[5] = {11, 3, 8, 777, -22};
    int i, j;
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 0;

    for(i = 1; i < size; i++)
    {
        key = arr[i];   //save arr[i] as key (i starts from 1). compare it with arr[i - 1] to arr[0]
        j = i - 1;      //j is from j - 1 to 0
        while(j >= 0 && key < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    for(i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void del_spaces_3()
{
    char str[] = "sh    o m   e! ";
    char *p = str;
    char *q = str;

    while(*p != '\0')
    {
        if(*p == ' ')
        {
            q = p;

            while(*q != '\0')
            {
                *q = *(q + 1);
                q++;
            }
            *q = '\0';
            p--;
        }
        p++;
    }

    printf("%s\n", str);
}
//TODO

void decode_print()
{
#ifdef way1
    char *str = "1234";
    int arr[] = {0};
    int val = atoi(str);
#endif

#ifdef way2
    char *str = "1234";
    int val;
    sscanf(str, "%d", &val);
#endif

#ifdef way3
    char *str = "1234ABC";
    char *ptr = NULL;               //point to where the number stops, it's "ABC"
    int val = strtol(str, &ptr, 10);
#endif

#ifdef way4     //one by one to parse
    char c = 'A';
    int x;
    x = c - 0x40;
#endif

    char str[] = " 1 234";
    char *ptr = NULL;
    long val = strtol(str, &ptr, 10);
    printf("%ld\n", val);
    printf("%s\n", ptr);
}



int main(void)
{
    //print_bin(8);
    //print_bin2(8);
    //reverse_str();
    //del_space_2();
    //insect_sorting();
    //del_spaces_3();
    decode_print();


    return 0;
}