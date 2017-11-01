
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#include <stdbool.h>
#include "color.h"


void print_trace()
{
    my_trace(BRIGHT, GREEN, BLACK, "good\n");
}

long fibonacci_ext(int num)
{
    long i, t_L = 0, t_LL = 0, tmp = 0, t = 0;

    for (i = 0; i <= num; i++)
    {
        if ((i == 0) || (i == 1))
        {
            t    = 1;
            t_LL = 1;
            t_L  = t;

            printf("t = %d\n", t);
            continue;
        }

        t    = t_LL + t_L;
        t_LL = t_L;
        t_L  = t;

        printf("i = %d\t", i);
        printf("t = %d\t", t);
        printf("t_L = %d\t", t_L);
        printf("t_LL = %d\n", t_LL);
    }

    return t;
}

long fibonacci_rec(int n)
{
    long result;

    if (n == 0 || n == 1)
    {
        result = 1;
    }
    else
    {
        result = fibonacci_rec(n - 1) + fibonacci_rec(n - 2);
    }

    return result;
}

int main(void)
{
    long x = fibonacci_ext(8);

//	long x = fibonacci_rec(8);

    printf("x = %ld\n", x);

    return 0;
}
