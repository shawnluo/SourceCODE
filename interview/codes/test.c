
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
        1.7 write an algorithm such that if an element in an MxN matrix is 0, then set its entire row and column to 0
            1 0 1      -->      0 0 0
            1 1 1               1 0 1
*/


/*
    

*/



int main()
{
    char *str = " ";
    char str_new[100] = {};

    int ret = replace_space(str, str_new);

    //printf("%d\n", ret);
    printf("%s\n", str_new);

    return 0;
}
