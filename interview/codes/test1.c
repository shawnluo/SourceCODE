#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



int main(void)
{
   int i = ~(0/2);
    printf("%ld\n", i);
    return 0;
}