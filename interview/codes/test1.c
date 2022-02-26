#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    1.2 reverse a c-style string
*/

int test(int *i)
{
    *i = 5;

    return 0;
}




int main()
{
    int i = 1;
    int ret = test(&i);
    printf("%d\n", i);

    return 0;
}