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



void print_bin(int num)
{
    if(num == 0)
    {
        printf("%d", 0);
        return;
    }
    if(num == 1)
    {
        printf("%d", 1);
        return;
    }
    if(num > 1)
    {
        int x = num % 2;
        num = num / 2;

        print_bin(num);
        printf("%d", x);
    }
}

void print_bin_ext(int num)
{
    char *c = (char *)&num;

    c += 3;
    for(int k = 0; k < 4; k++)
    {
        for(int i = 7; i >= 0; i--)
        {
            //printf("\n*c: 0x%x\n", *c);
            if(*c & (1 << i))
                printf("%d", 1);
            else
                printf("%d", 0);
        }
        c--;
        printf(" ");
    }
    printf("\n");
}





int main(void)
{
    print_bin_ext(9);
    //printf("0x%x", val);
    return 0;
}