#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
    1. the first loop goes through str
    2. the second loop goes through substr
        1). if find the matched char, then next char;
        2). if NOT, break
    3. 
*/
int is_substring(char *str, char *substr)
{
    int len1 = strlen(str);
    int len2 = strlen(substr);

    int i, j, k;
    char *p1 = str;
    char *p2 = substr;

    for(i = 0; i < len1; i++)
    {
        k = i;
        for(j = 0; j < len2; j++)
        {
            //printf("%c %c\n", p1[k], p2[j]);
            if(p1[k] == p2[j])
            {
                k++;
            }
            else
            {
                break;
            }
        }
        if(p2[j] == '\0')
        {
            return 0;
        }   
    }
   
   return -1;
}

int main()
{
    char *str = "show me!bhs";
    char *substr = "showm";

    printf("%s\n", is_substring(str, substr) == 0 ? "yes" : "no");

    return 0;
}