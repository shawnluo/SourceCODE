#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


int num_conver(int a, int b)
{
    int val  = a ^ b;
    int cnt = 0;
    while(val)
    {
        if(val & 1) ++cnt;
        val >>= 1;
    }
    return cnt;
}

int main(void)
{
    int val;
    val = num_conver(4, 10); //0100 1100
    printf("%d\n", val);

    return 0;
}