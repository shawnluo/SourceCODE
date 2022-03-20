

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
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


/*
    coins: 1 cnets, 5 cents, 10 cents
    sum:
    requirement:
        1. how many ways?
        2. print the solutions

    formular:
        parameters:
            sum: coins total value
            ways: the ways to finish the combination
        f(sum, N, ways) = 
            switch(sum)
            {
                case 10:
                    f(sum + 5, N, ways)
            }


    formular:
        f(sum):
            return f(sum + 1)
            return f(sum + 5)
            return f(sum + 10)
    exit:
        if(sum == N)    cnt++;
*/
int f()
{

}

int main(void)
{
    int arr[] = {1, 2000, 8700, 5, 8, 0, 654};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", f(arr, 4));

    return 0;
}