

#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
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


int partition(int *arr, int low, int high)
{
    int key;
    key = arr[low];
    while(low < high)
    {
        while(low < high && arr[high] >= key)
            high--;

        if(low < high)
            arr[low++] = arr[high];

        while(low < high && arr[low] <= key)
            low++;

        if(low < high)
            arr[high--] = arr[low];
    }
    arr[low] = key;

    return low;
}

void quick_sort(int *arr, int start, int end)
{
    int pos;
    if(start < end)
    {
        pos = partition(arr, start, end);
        quick_sort(arr, start, pos - 1);
        quick_sort(arr, pos + 1, end);
    }
}


void mySort(int *arr, int size)
{
    int left = 0, right = size - 1;

    quick_sort(arr, left, right);
}

int main(void)
{
    int A[5] = {0, 5, 4, 2, 1};

    //mySort(A, 5);
    quick_sort(A, 0, 4);

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
