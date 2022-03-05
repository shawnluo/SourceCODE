
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
    32-bit numbers, N and M, and two bit positions, i and j.
    wirte a method to set all bits beween i = 3 and j = 6 in N equal to M
    101 0000 110   --> 101 1111 111
        6  3
        1111
*/
int bit_op(int m, int n, int i, int j)
{
    //1. in N, clean i to j to 0;
    //2. shift M to left for i bits
    //3. N || M

    int max = ~0;

    //left: 1's through j, then 0's
    int left = max - ((1 << j) - 1);
    //right: 1's after i
    int right = (1 << i) - 1;
    
    int mask = left | right;
    return (n & mask) | (m << i);
}

void print_bin(int n)
{
    if(n > 0)
    {
        print_bin(n / 2);
    }
    else
    {
        return;
    }
    printf("%d ", n % 2);
}

int main(void)
{
    int val = bit_op(111, 5, 2, 4);
    printf("%d\n", val);
    print_bin(5);
    printf("\n");
    return 0;
}