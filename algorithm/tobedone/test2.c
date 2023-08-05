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

typedef struct DATA {
    int i;
    int j;
}data;

//find the max in arr
data test()
{
    data x;
    x.i = 34;
    x.j = 1009;

    for(int i = 0; i < 10; i++) {
        if(i == 5) {
            break;
        }
        printf("i = %d\n", i);
    }
    printf("xxxxxxxxx\n");

    return x;
}

int main(void)
{
    int arr[] = {1, 2, 1, 1, 1, 2};

    //max_fun(arr, sizeof(arr) / sizeof(arr[0]));
    //printf("min = %d\nmax = %d\n", min, max);

    data ret = test();



    return 0;
}