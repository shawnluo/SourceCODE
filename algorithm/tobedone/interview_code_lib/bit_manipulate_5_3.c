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

int next_bigger(int n)
{
    int cnt = cal_one(n);
    //next smallest bigger
    while(n <= INT_MAX)
    {
        n += 1;
        if(cal_one(n) == cnt)
        {
            return n;
        }
    }

    return -1;
}

int next_smaller(int n)
{
    int cnt = cal_one(n);
    while(n >= INT_MIN)
    {
        n -= 1;
        if(cal_one(n) == cnt)
        {
            return n;
        }
    }

    return -1;
}

int main()
{
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
}