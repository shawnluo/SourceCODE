#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*
    find all the substrings, save them to the substring[] dynamatically;

    1234

    - 1, 12, 123, 1234
    - 2, 23, 234
    - 3, 34
    - 4
*/



void find_all_substr(const char *str)
{
    char **substr;
    int len = strlen(str);
    int i, j, k = 0;

    for(i = 0; i < len; i++)
    {
        for(j = i; j < len; j++)
        {
            for(k = 0; k < j; k++)
            {
                printf("%c", str[k]);
            }
            printf("\t");
        }
        printf("\n");
    }
}

int main(void)
{
    char str[10] = "show";

    find_all_substr(str);

    //printf("2 - %s\n", str);
    //for(int i = 0; i < sizeof(str2); i++)
    //printf("%c\t", str2[i]);
    //printf("\n");
    //printf("%d\n", strcmp("abcd", "abc"));
    return 0;
}