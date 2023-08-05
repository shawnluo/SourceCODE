#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>




int main(void)
{
    char **s;
    int n = 5;
    int i, j;

    char *arr[] = {"ab", "cd", "ef", "gh", "ij"};

    s = calloc(5, sizeof(char *));
    for(i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char));
        s[i] = arr[i];
    }

    if(n == 1)
    {
        return 1;   //only 1 string, no need to delete the duplicate
    }

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            //printf("%s\t%s\n", s[i], s[j]);
            if(strcmp(s[i], s[j]) == 0)
            {
                while(j + 1 < n)
                {
                    s[j] = s[j + 1];
                    j++;
                }
                i--;
                n--;
            }
        }
    }

    printf("n = %d\n", n);

    for(int i = 0; i < n; i++)
    {
        printf("%s\n", arr[i]);
    }



    return 0;
}