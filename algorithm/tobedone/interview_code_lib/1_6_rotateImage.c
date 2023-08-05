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


int rotate_img(int arr[][3], int size)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            int tmp = arr[j][i];
            arr[j][i] = arr[i][j];
            arr[i][j] = tmp;
        }
    }
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
#if 1
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size / 2; j++)
        {
            printf("%d, %d ", j, arr[i][size - j - 1]);
            int tmp = arr[i][size - j - 1];
            arr[i][size - j - 1] = arr[i][j];
            arr[i][j] = tmp;
        }
        printf("\n");
    }
    printf("\n");
#endif
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}


int main(void)
{
    int arr[3][3] = {{1, 2, 3}, {10, 20, 30}, {100, 200, 300}};
    //char * rep = ""
    rotate_img(arr, 3);
    //printf("%s\n", arr);

    return 0;
}