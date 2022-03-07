#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

int cnt = 0;
//print the all the permutation 
void list_permutation(char *str, int left, int right)
{
    //statio int cnt = 0;
    int i;
    if(left == right)
    {
        cnt++;
        //printf("%s\n", str);
    }
    else
    {
        for(i = left; i <= right; i++)
        {
            swap((str + left), (str + i));
            list_permutation(str, left + 1, right);
            swap((str + left), (str + i));
        }
    }
}

int main(void)
{
    char str[] = "abcdef";
    //char *arr[] = {"ab", "cd", "ef", "gh", "ij"};
    int n = strlen(str);
    list_permutation(str, 0, n - 1);
    printf("%d\n", cnt);
    return 0;
}

#if 0
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

    char *s2[]= {NULL};

    for(i = 0; i < n; i++)
    {
        s2[i] = calloc(11, sizeof(char));
        strcpy(s2[i], s[i]);
    }

    for(i = 0; i < n; i++)
    {
        //printf("%s\n", s[i]);
    }

    int x = 0;
    //calculate the x, fibonachi

    for(i = 0; i < x; i++)
    {

    }


    for(i = 0; i < n; i++)
    {
        free(s2[i]);
    }
    


    return 0;
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
#endif