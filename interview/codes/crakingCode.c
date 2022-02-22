
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
        1.1. determin if a string has all unque char
*/

/*
    initialize a int arr[128], set to 0
    then go through the string, add 1 to the arr[*str].
    if the arr[*str] = 1, then return
*/
int Is_unique(const char *str)
{
    if(!str)
    {
        printf("str is invalid!\n");
        return -1;
    }

    int arr[128] = {0};
    while(*str != '\0')
    {
        //arr[*str] = 1;
        if(arr[*str] == 0)
        {
            arr[*str] = 1;
        }
        else
        {
            return 1;
        }

        str++;
    }
    return 0;
}

int main()
{
    const char *arr = "showme";

    printf("%d\n", Is_unique(arr));

    return 0;
}



/*
        1.2 reverse a C-Style String
*/

/*
    using char *pStart to point to the string start,
    char *pEnd to point to the string end
    save pStart to tmp;
    while loop, (condition : pStart < pEnd)
        swap pStart and pEnd, then pStar++, pEnd--
*/
int reverse_str(char *str)
{
    if(!str)
    {
        printf("invalid string!\n");
        return -1;
    }

    char *pStar = str;
    char *pEnd = str + strlen(str) - 1;
    char tmp;

    while(pStar < pEnd)
    {
        tmp = *pStar;
        *pStar = *pEnd;
        *pEnd = tmp;
        pStar++;
        pEnd--;
    }

    return 0;
}

int main()
{
    char arr[] = "showme";
    if(reverse_str(arr) == -1)
    {
        return -1;
    }

    printf("%s\n", arr);

    return 0;
}


/*
        1.3 remove the duplicat char in a string without using any additional buffer
            can NOT use extra copy of the array
*/


/*
    1. move str[n + 1] to str[n], untile str[n + 1] == '\0'
    2. 
*/
int move_str(char *str)
{
    if(!str)
    {
        printf("str is empty!\n");
        return -1;
    }

    while(*str != '\0')     // if *str is '\0', then just copy it as an string end char
    {
        *str = *(str + 1);
        str++;
    }

    return 0;
}


/*
    str: "abcaaabc" --> "abc"
    1. first while loop ( condition: str != '\0'):
        goes through from the beginning of str, 
    2. second  loop:
        *p, goes through from the str + 1.
        if *str == *p, then move the flowing char step forward
        add '\0' to the end of str
*/
int remove_dup_str(char *str)
{
    if(!str)
    {
        printf("invalid string!\n");
        return -1;
    }

    char *p = str;

    //abcabaaa
    while(*str != '\0')
    {
        //printf("%c\n", *(str + 1));
        for(p = str + 1; *p != '\0'; p++)
        {
            if(*str == *p)
            {
                move_str(p); // move *(P + 1) to *p, until the end of str
                p--;            // just in case there are multiple same character like "abccc", so need to recheck it
            }
        }
        str++;
    }

    return 0;
}

int main()
{
    char arr[] = "abcaaabbbaa";
    if(remove_dup_str(arr) == -1)
    {
        return -1;
    }

    printf("%s\n", arr);

    return 0;
}



/*
        1.4 decide if 2 strings are anagrams or not
            "abc"    -   "bac"
*/


/*
    initize a int data1[128], go through the str, increase arr[*str] when meet *str,
    run the same function for another str, generate a data2[128],
    if the data1 equal data2. then they are anagrams
*/
int Is_anagrams(char *str1, char *str2)
{
    if((!str1) || (!str2))
    {
        printf("str is empty!\n");
        return -1;
    }

    int i;
    char data1[128] = {0};
    char data2[128] = {0};

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if(len1 != len2)
        return 1;

    for(i = 0; i < len1; i++)
    {
        //printf("*str1 = %d\n", *str1);
        data1[*str1++]++;
    }

    for(i = 0; i < len2; i++)
    {
        data2[*str2++]++;
    }

    for(i = 0; i < 128; i++)
    {
        if(data1[i] != data2[i])
        {
            //printf("%c, %c\n", data1[i], data2[i]);
            return 2;
        }
    }

    return 0;
}



int main()
{
    char *arr1 = "show me";
    char *arr2 = "me owsh";
    int ret = Is_anagrams(arr1, arr2);

    printf("%d\n", ret);

    return 0;
}
