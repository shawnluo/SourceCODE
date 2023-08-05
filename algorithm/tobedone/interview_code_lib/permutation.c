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