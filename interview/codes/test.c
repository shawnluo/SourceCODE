#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


//1. how to treat two demension pointer arr as one demension
//2. 

#if 0
void test(char **s, int len)
{
    int i, j;
    char *arr[100];
    int k = 0;

    for(i = 0; i < len; i++)
    {
        arr[i] = (char *)malloc(1000);
    }

    for(i = 0; i < len; i++)
    {
        printf("s[%d]: %s\n", i, s[i]);
        for(j = 0; s[i][j] != '\0'; j++)
        {
            if(s[i][j] != ' ')
            {
                strcat(arr[k], s[i][j]);
                ++k;
            }
            else
            {
                strcat(arr[k], '\0');
                ++k;
            }
        }
    }

    for(i = 0; i < k; i++)
    {
        printf("%s\n", arr[i]);
    }
}
#endif

void extract(char *s)
{
    char s1[50];
    char s2[50];
    int i_1, i_2;

    int i;
    while(*s != '\0')
    {
        i = 0;
        while(*s != ' ')
            s1[i++] = *s++;
        s1[i] = '\0';

        s++, i = 0;
        while(*s != ' ')
            s2[i++] = *s++;
        s2[i] = '\0';

        break;
    }
    i_1 = atoi(s1);
    i_2 = atoi(s2);
    printf("i_1: %d\n", i_1);
    printf("i_2: %d\n", i_2);
}


int main(void)
{
    //char *p[] = {"11 2 100", "2 3 200", "11 2 200"};

    char *str = "11 2 100";
    extract(str);

    return 0;
}