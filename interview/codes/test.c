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


mask = ~0;
left = mask - ((1 << j) - 1);
right = (1 << i) - 1;
mask = left | right;
N = N | mask;
M <<= 2;
N = N | M;


int main(void)
{
    print_bin_ext(9);
    //printf("0x%x", val);
    return 0;
}

int n = 123;
char *c = (char *)&n;

c += 3;

for(i = 0; i <= 3; i++)
{
    for(j = 7; j >= 0; j--)
    {
        if(*c & (1 << j))
            print 1;
        else
            print 0;
    }
    c--;
}

char *str = "3.72";
int size = strlen(str);
int i;
for(i = 0; i < size; i++)
{
    if(str[i] != '.')
    {
        newArr[i] = str[i];
    }
    else
    {
        newInt[i] = '\0';
        break;
    }
}

//rec
//123
int conv(char *str)
{
    int size;
    if(strlen(str) == 1)
    {
        return str[0] - '0';
    }
    else
    {
        size = strlen(str);
        str[size - 1] = '\0';
        return conv(str) * 10 + (str[size - 1] - '0');
    }
}

//123.456



while(*str != '.')
{
    str++;
}

new_decimal[0] = '.'
for(i = 0; i < size; i++)
{
    new_decimal[i + 1] = str[i];
}


void decimal_bin(float f)
{
    if(f == 0.0)
        print 0;
    else if(f == 1.0)
        print 1;
    else
    {
        mod = (f * 2) >= 1 ? 1 : 0;
        f = (f * 2) >= 1 ? (f * 2 - 1) : (f * 2);
        decimal_bin(f);
    }
}

// pow(2, n);

int mypow(int base, int n)
{
    if(n == 0)
        return 1;
    if(n == 1)
        return base;

    return base * mypow(base, n - 1);
}

5   101
7   111
c = a ^ b
1' in c

while(a || b)
{
    if((!a) || (!b))
    {
        cnt++;
        continue;
    }
    if((a && 1) == (b && 1))
        cnt++;
}

a = 0x55555555      0101 0101 0101 0101
b = 0xaaaaaaaa      1010 1010 1010 1010

(n & a) << 1
(n & b) >> 1


a[1...4]
0 1 3 4

0
01
10
11
100
101


the final bit

for(i = 1; i <= n; i++)
{
    end1 = A[i] & 1; 
    if(end1 == end2)
    {
        printf("%d is missing\n", i - 1);
    }
    end2 = end1;
}


int fib(int n)
{
    if n == 0
        return 0;
    if n == 1
        return 1;
    return fib(n - 1) + fib(n - 2);
}


int robot(int x, int y)
{
    if(n == 1)
        return 1;
    return robot(x, y - 1) + robot(x - 1, y);
}