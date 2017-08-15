
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include "color.h"



#define Row       5
#define Column    7


void fun(int k, int *p)
{
    int a, b;

    if (k == 1 || k == 2)
    {
        *p = 1;
    }
    else
    {
        fun(k - 1, &a);
        fun(k - 2, &b);
        *p = a + b;
    }
}

int main(void)
{
    int x;

    fun(6, &x);
    printf(" %d\n ", x);
    return 0;
}

