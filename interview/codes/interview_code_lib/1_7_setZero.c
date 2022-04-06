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


void print_arr(int arr[][3], int size)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void set_zero(int arr[][3], int size, int x, int y)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if((i == x) || (j == y))
            {
                arr[i][j] = 1;
            }
        }
    }
}

void set_arr(int arr[][3], int size)
{
    int i, j;
    int arr_new[3][3] = {0};

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(arr[i][j] == 0)
            {
                set_zero(arr_new, size, i, j);
                print_arr(arr_new, size);
                //exit(0);
            }
        }
    }

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(arr_new[i][j] == 1)
            {
                arr[i][j] = 0;
            }
        }
    }
}


int main(void)
{
    int arr[3][3] = {{1, 0, 3}, {10, 20, 30}, {0, 200, 300}};
    //char * rep = ""
    set_arr(arr, 3);
    print_arr(arr, 3);

    return 0;
}