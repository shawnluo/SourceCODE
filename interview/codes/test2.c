#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>
#include <limits.h>

//int min = -(1 << 31);
//int max = (1 << 31) - 1;

int min = INT_MIN;
int max = INT_MAX;

//find the max in arr
void max_fun(int *arr, int len)
{
    min = arr[0];
    max = arr[0];
    for(int i = 0; i < 5; i++)
    {
        if(arr[i] <= min)   min = arr[i];
        if(arr[i] >= max)   max = arr[i];
    }

    printf("min = %d\nmax = %d\n", min, max);
}

int main(void)
{
    int arr[] = {1, 2, 1, 1, 1, 2};

    max_fun(arr, sizeof(arr) / sizeof(arr[0]));
    printf("min = %d\nmax = %d\n", min, max);

    return 0;
}