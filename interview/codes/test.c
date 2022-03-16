#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>


typedef struct Data
{
    int id;
    struct Data *next;
}data, *pData;


pData create_ll(int *arr, int size)
{
    
}

int rm_dup()
{
    return 0;
}

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};
    pData pHead = create_ll(arr, 5);
    return 0;
}