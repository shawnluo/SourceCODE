
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>



/*
                                Hanoi tower


                plates          rod_0          rod_1           rod_2
    1. move n-1 plates      from  : rod_0    to    : rod_1    buffer: rod_2
    2. move 1   plate       from  : rod_0    buffer: rod_1    to    : rod_2
    3. move n-1 plates      buffer: rod_0    from  : rod_1    to    : rod_2
*/
int Hanoi(int n, int from, int buffer, int to)
{
    if(1 == n)
    {
        printf("Move %d:   %d    -->    %d\n", n, from, to);
        return 0;
    }
    else
    {
        Hanoi(n - 1, from,    to,    buffer);
        Hanoi(1,     from ,  buffer, to);
        Hanoi(n - 1, buffer, from, to);
    }

    return 0;
}

int main(void)
{
    Hanoi(5, 0, 1, 2);
    return 0;
}