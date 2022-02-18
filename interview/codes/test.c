#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void set_longest(char *tmp, char *longest_substr)
{
    printf("1 - %s, %s\n", tmp, longest_substr);
    if(strlen(longest_substr) < strlen(tmp))
    {
        strcpy(longest_substr, tmp);
    }
    printf("2 - %s\n", longest_substr);
}

/* find the longest substring of a string containing distinct characters
      1. from the beginning of strng, find the distinct string, and calculate the length. save it to longest_str[];
            a. how to find the distinct string?
                1. inilize a 128 units integer array with 0;
                2. from the first of the string, set the array to 1 if it was 0, else the loop stops.
      2. continue to find the distinct string, if the new one is longer than the saved longest_str, then replace the longest_str with the new one.
      3. untile the double for loop finished.
*/
void func(char *str)
{
    int data[128] = {0};
    char longest_substr[100] = {0};
    char tmp[100] = {0};
    int pos;

    if(!str)
    {
        perror("str must NOT be empty!");
        return -1;
    }
    
    int cur_pos = 0;
    int len = strlen(str);
    int i, flag = 0;

    for(i = 0; i < len; i++)
    {
        for(int j = i; j < len; j++)
        {
            if(data[str[j]] == 0)
            {
                data[str[j]] = 1;
                tmp[pos++] = str[j];
            }
            else
            {
                tmp[pos] = '\0';
                pos = 0;
                set_longest(tmp, longest_substr);
                //printf();
                memset(tmp, 0, 100);
                memset(data, 0, 128);
                break;
            }
        }
    }
    tmp[pos] = '\0';

    printf("%s\n", longest_substr);
}


int main()
{
    int n;
    //scanf("%d", &n);
    n = 4;

    char *str = "show me!bhs";
    func(str);

    return 0;
}