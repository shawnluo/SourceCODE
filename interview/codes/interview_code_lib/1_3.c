#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    1.3 remove the duplicate characters in a string
*/

int test()
{
    char str[100] = "abcadaadffdda";
    int len = strlen(str);
    char *p = str;

    // go through str, find same char then, 1.move the following char forward.
    //                                   or 2. strcpy the str from the next to current

    for(int i = 0; str[i] != '\0'; i++)
    {
        for(int j = i + 1; str[j] != '\0'; j++)
        {
            if(str[i] == str[j])
            {
                strcpy(str + j, str + j + 1);
                j--;
            }
        }
    }

    printf("%s\n", str);
    return 0;
}

int test1()
{
    char str[100] = "13222145112";
    char *p = str;

    for(int i = 0; str[i] != '\0'; i++)
    {
        for(int j = i + 1; str[j] != '\0'; j++)
        {
            // if arr[i] == arr[j], then loop to move str[j] = str[j + 1]
            if(str[i] == str[j])
            {
                int k = j;
                while(str[k] != '\0')
                {
                    str[k] = str[k + 1];
                    k++;
                }
                j--;
            }
        }
    }

    printf("%s\n", str);
}


int main()
{
    int ret = test1();
    //printf("%d\n", ret);

    return 0;
}