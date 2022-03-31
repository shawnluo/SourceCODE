

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

int ones = 0;

int test(int base, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return base;

    return base * test(base, n - 1);
}

void sorting(int *arr, int left, int right)
{
    //find the 
    int center = find_center();
    forting(arr, left, center - 1);
    sorting(arr, center + 1, right);
}


int mySort(int *arr, int size)
{
    int left = 0, right = size - 1;

    sorting(arr, left, right);
}

int main(void)
{
    int end1 = 0, end2 = 1;
    int A[5] = {0, 5, 4, 2, 9};

    mySort(A, 5);

    return 0;
}
