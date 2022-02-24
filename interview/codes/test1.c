#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    1.2 reverse a c-style string
*/

int test()
{
    char *str = "abcd";
    int len = strlen(str);
    char *reverse = (char *)malloc();

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
    int arr[5] = {3, 1, 2, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    int i, j, tmp;
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

    for(i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    

    return 0;
}


// insect sorting str, then go through and see the neighboring characters are identical
int test3()
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