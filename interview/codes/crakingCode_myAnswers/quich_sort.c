#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


int partition(int *arr, int low, int high)
{
    int pos = arr[low];

    while(low < high)
    {
        //1. from right move to left, skip the elements which >= pos
        while(low < high && arr[high] >= pos)
            high--;

        //2. if element < pos, then arr[low] = arr[high], then low++
        if(low < high)
            arr[low++] = arr[high];

        //3. from left move to right, skip the element which < pos
        while(low < high && arr[low] <= pos)
            low++;

        //4. if element >= pos, then swith it with arr[high], then high--
        if(low < high)
            arr[high--] = arr[low];
    }
    arr[low] = pos;
    //or arr[high] = pos;

    return low;
    //or return high;
}

void quick_sort(int *arr, int low, int high)
{
    if(!arr)
    {
        printf("arr is invalid!\n");
        return;
    }

    int pos;
    if(low < high)
    {
        pos = partition(arr, low, high);
        quick_sort(arr, low, pos - 1);
        quick_sort(arr, pos + 1, high);
    }
}

int main(void)
{
    int arr[5] = {4, 3, 1 ,5, 2};
    quick_sort(arr, 0, 4);

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}