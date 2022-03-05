
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


void test()
{
    int volatile *reg = (int *)0x80000000;
    *reg |= 0x800000000;
    *reg &= 0x7fffffff;
}

int main()
{
    return 0;
}