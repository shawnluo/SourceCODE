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

int fib(int n)
{
    if(n <= 0)  return n;
    
    int memo[100] = {0};
    memo[0] = 0;
    memo[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        memo[i] = memo[i - 1] + memo[i - 2];
    }
    return memo[n];
}


for(i = 2; i <= n; i++)
{
    memo[i] = memo[i - 1] + memo[i - 2];
}
return memo[n];


int main()
{
    int val = fib(5);
    printf("%d\n", val);

    return 0;
}
