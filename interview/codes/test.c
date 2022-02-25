
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
    char str[5] = "\0";
    //"12345";
    str[0] = '1';
    str[1] = '2';
    str[2] = '3';
    str[3] = '4';
    //str[4] = '5';
    //str[5] = '6';
    printf("%d\n", sizeof(str));
    printf("%d\n", strlen(str));
    printf("%d\n", str[4]);
}

int main()
{
    test();
    return 0;
}
