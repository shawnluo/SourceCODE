#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

int max(int x, int y)
{
    return x >= y ? x : y;
}

//arr[5] = {1, 5, 2, 4, 3};
//Return the length of longest increasing subsequence starting from start
int longest(int arr[], int len, int start)
{
    if(len - 1 == start)    return 1;

    int max_len = 1;

    for(int j = start + 1; j < len; j++)
    {
        if(arr[j] > arr[start])
            max_len = max(max_len, longest(arr, len, j) + 1);
    }

    return max_len;
}

int save[1000] = {0};

int longest_ext(int arr[], int len, int start)
{
    if(save[start] != -1)   return save[start];
    
    int max_len = 1;

    for(int i = start + 1; i < len; i++)
    {
        if(arr[i] > arr[start])
            max_len = max(max_len, longest_ext(arr, len, i) + 1);
    }

    save[start] = max_len;
    return max_len;
}

int main(void)
{
    //int arr[] = {10, 2, 5, 2, 4, 3, 7, 8};
    int arr[] = {10, 200, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 17, 8, 10, 2, 5, 2, 4, 113, 7, 438, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 810, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 802, 10, -2, 5, 2, 4, 3, 7, 8, 10000, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 17, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 810, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8, 10, 2, 5, 2, 4, 3, 7, 8 };
    int len = sizeof(arr) / sizeof(arr[0]);

    //int val = longest(arr, len, 0);
    //printf("%d\n", val);

    for(int i = 0; i < 1000; i++)
    {
        save[i] = -1;
    }

    int max_len = 1;
    for(int i = 0; i < len; i++)
    {
        max_len = max(max_len, longest_ext(arr, len, i));
    }
    printf("max_len: %d\n", max_len);
}