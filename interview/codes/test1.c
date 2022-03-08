#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

int cnt = 0;
void print_bin(int i)
{

    if(i > 0)
    {
        print_bin(i / 2);
    }
    else
    {
        return;
    }
    cnt++;
    printf("%d ", i % 2);
}

int cal_one(int n)
{
    int cnt = 0, i;

    //Do NOT use while(n > 0), because n can be negtive number.
    /*
    while(n > 0)
    {
        if ((n & 1) == 1)
        {
            cnt++;
        }
        n = n >> 1;
    }
    */
    for(i = 0; i < 32; i++)
    {
        if((n & 1) == 1)
        {
            cnt++;
        }
        n >>= 1;
    }

    return cnt;
}

//go through a and b from lowest bit
int change_one(int a, int b)
{
    int i, cnt = 0;

    for(i = 0; i < 32; i++)
    {
        if((a & 1) != (b & 1))
        {
            cnt++;
        }
        a >>= 1;
        b >>= 1;
    }
    return cnt;
}

int change_one_ext(int a, int b)
{
    int i, cnt = 0;

    for(i = a ^ b; i > 0; i = i >> 1)
    {
        cnt += i & 1;
    }

    return cnt;
}


//swap even adn odd bits
//0101  -->  1010

int swap_bit(int n)
{
    //0xaa: 10101010
    //0x55: 01010101
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    return n;
}

//recursive
int fibo(int i)
{
    if(0 == i)
    {
        return 0;
    }
    else if(1 == i)
    {
        return 1;
    }
    else
    {
        return (i + fibo(i - 1));
    }
}

//iteration
int fibo_ext(int i)
{
    if(0 == i)
    {
        return 0;
    }
    else if(1 == i)
    {
        return 1;
    }
    else
    {
        for(i = 0; i <= n; i++)
    }
}

int main()
{
    printf("%d\n", fibo(3));
#if 0
    int i =0x8;
    int val = swap_bit(i);

    print_bin(i);
    printf("\n");

    print_bin(val);
    printf("\n");

    int val = change_one_ext(1, 2); //10    11
    printf("%d\n", val);

    return 0;

    int i = 17;
    int val = next_bigger(i);
    print_bin(i);
    printf("\n");

    print_bin(val);
    printf("\n");

    val = next_smaller(i);
    print_bin(i);
    printf("\n");

    print_bin(val);
    printf("\n");

    return 0;
#endif
}