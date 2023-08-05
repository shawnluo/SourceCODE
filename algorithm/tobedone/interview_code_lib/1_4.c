#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
    1.4 decide if two strings are anagrams or not
*/

int test()
{
    char *str1 = "15432";
    char *str2 = "12345";

    // go through str1, save the ascii code to char data1[128]
    // go through str2, save the ascii code to char data2[128]
    // compare the 2 strings

    char data1[128] = {0};
    char data2[128] = {0};
    while(*str1 != '\0')
    {
        data1[*str1]++;
        str1++;
    }

    while(*str2 != '\0')
    {
        data2[*str2]++;
        str2++;
    }

    int i = 0;
    while(i < 128)
    {
        if(data1[i] != data2[i])
        {
            return -1;
        }
        i++;
    }

    return 0;
}


void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


void sorting_bubble(char *str)
{
    int i, j;
    int len = strlen(str);

    for(i = 0; i < len - 1; i++)
    {
        for(j = i + 1; j < len; j++)
        {
            if(str[i] > str[j])
            {
                swap(&str[i], &str[j]);
            }
        }
    }
}

/*
    sorting the 2 strings
    compare the 2 strings
*/
int test1()
{
    char str1[10] = "12t45";
    char str2[10] = "13245";



    /* sorting str1
        bubble:
            a b c d

    */
    sorting_bubble(str1);
    sorting_bubble(str2);

    printf("%s\n", str1);
    printf("%s\n", str2);

    return strcmp(str1, str2) ? 1 : 0;
}


int main()
{
    int ret = test1();
    printf("%d\n", ret);

    return 0;
}