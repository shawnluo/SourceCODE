#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


/*
    A[1...n] contains integer [0, n], 
    we can use "int fetch(int *arr, i, j)" to get jth bit of arr[i],
    find the missing integer
    solution:
        we can use fetch() to get arr[i], then save it to an newArr[], then
        we can find the missing one.
*/
int find_missing(int *arr, int len)
{
    int val = 0;
    int newArr[len] = {0};
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            bit = fetch(arr, i, j);
            bit << j;
            val = val + bit;
        }
        newArr[i] = val;
    }
}


int main(void)
{
    int val;
    val = find_missing(4, 10);
    printf("%d\n", val);

    return 0;
}