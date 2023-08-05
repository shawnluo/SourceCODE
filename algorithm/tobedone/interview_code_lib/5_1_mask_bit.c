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


/*
    100100000000
         10101
         j   i
*/

//0. get mask
//  1). mask = ~0
//  2). get left: left = mask - ((1 << j) - 1)
//  3). get right: right = (1 << i) - 1
//  4). mask = left | right
//1. get mask all 1 but 6~2 all 0
//2. data = data & mask
//3. m << 2
//4. data |= m

int test()
{
    int mask = ~0;
    int left = mask - ((1 << 6) - 1);
    int right = (1 << 2) - 1;
    mask = left | right;

    int m = 0x15;
    m <<= 2;
    int data = 0x1000;
    data |= m;

    return data;
}


int main(void)
{
    int val = test();
    printf("0x%x", val);
    return 0;
}