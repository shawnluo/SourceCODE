#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>



int robot_move(int m, int n)
{
    if(m == 1) return 1;
    if(n == 1) return 1;
    return robot_move(m, n - 1) + robot_move(m - 1, n);
}


int main(void)
{
    int val;
    val = robot_move(2, 2);
    printf("%d\n", val);

    return 0;
}