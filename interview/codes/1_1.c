#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    1.1 determine if a string has all unique characters.
*/



// just go through the string to find if it's unique or not
int test()
{
    char *str = "good";
    char *p;

    while(*str)
    {
        for(p = str + 1; *p != '\0'; p++)
        {
            if(*str == *p)
            {
                return -1;
            }
        }
        str++;
    }
    return 0;
}





// insect sorting str, then go through and see the neighboring characters are identical
int test2()
{
    char arr[] = "acbex";
    int len = strlen(arr);
    int i, j;
    char tmp;

    for(i = 1; i < len; i++)
    {
        tmp = arr[i];
        j = i - 1;

        while(j >= 0 && tmp < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }

    //printf("%s\n", arr);

    // if the 2 neighbores are identical, then is not unique.
    for(i = 0; i < len; i++)
    {
        if(arr[i] == arr[i + 1])
        {
            return -1;
        }
    }

    return 0;
}


int main()
{
    int ret = test3();
    printf("%d\n", ret);

    return 0;
}