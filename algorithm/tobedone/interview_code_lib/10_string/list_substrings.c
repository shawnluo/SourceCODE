#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
    find all the substrings

    1234

    - 1, 12, 123, 1234
    - 2, 23, 234
    - 3, 34
    - 4
*/

void print_str(const char *str, int pos, int curLen)
{
    while(curLen--)
    {
        printf("%c", str[pos++]);
    }
    printf(", ");
}


void find_all_substr(const char *str)
{
    int pos, curLen, k;
    int len = strlen(str);

    for(pos = 0; pos< len; pos++)
    {
        for(curLen = 1; curLen <= len - pos; curLen++)
        {
            print_str(str, pos, curLen);
        }
        printf("\n");
    }
}


void find_all_substr_ext(const char *str)
{
    int i, j, k;
    int len = strlen(str);
    char *pTmp = str;
    int curLen = 0;
    for(i = 0; str[i] != '\0'; i++)
    {
        for(j = i; str[j] != '\0'; j++)
        {
            //for(k = i; str[k] != '\0'; k--)
            for(k=1;k <=j;k++)
            {
                pTmp = str;
                curLen =k;
                while(curLen > 0)
                {
                    printf("%c", *pTmp);
                    curLen--;
                    pTmp++;
                }
            }
            printf("\t");
        }
        printf("\n");
    }
}


int main(void)
{
    char str[10] = "1234";

    find_all_substr(str);

    //printf("2 - %s\n", str);
    //for(int i = 0; i < sizeof(str2); i++)
    //printf("%c\t", str2[i]);
    //printf("\n");
    //printf("%d\n", strcmp("abcd", "abc"));
    return 0;
}