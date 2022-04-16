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

typedef struct DATA
{
    int num;
    int repeat;
}data;

void test(int *arr, int len)
{
    data cal_repeat[5] = {0};
    //from index 0, find repeat add 1
    for(int i = 0; i < len; i++)
    {
        
    }
}

int main(void)
{
    int arr[] = {0, 1, 21, 4, 0, 1, 2, 76, 4};
    int len = sizeof(arr) / sizeof(arr[0]);
    test(arr, len);
    printf("%d - %d\n", arr[0], arr[1]);

    return 0;
}