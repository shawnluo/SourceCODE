#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


void get_2_int(char *s, int *arr)
{
    //printf("%s\n", s[i]);
    char *p = NULL;
    int k = 0;
    char s1[100], s2[100];
    //int arr[2] = {0};

    p = s;
    while(*p != ' ')
    {
        s1[k] = *p;
        ++k, ++p;
    }
    s1[k] = '\0', ++p;
    k = 0;
    
    while(*p != ' ')
    {
        s2[k] = *p;
        ++k, ++p;
    }
    s2[k] = '\0';

    //printf("%s, %s\n", s1, s2);
    arr[0] = atoi(s1);
    arr[1] = atoi(s2);

    printf("%d, %d\n", arr[0], arr[1]);
    //return arr;
}

void sorting(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = i + 1; j < len; j++)
        {
            if(arr[j - 1] < arr[j])
            {
                int tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}


//use repeat[i][j] to save the repeat numbers, {num1, repeat times}, {num2, repeat times}
void cal_repeat(int *arr, int len, int **repeat)
{
    
}

/*
    ""
*/
void extract_str(char **s, int len, int threshold)
{
    //char *p[100];
    //p = s;
    //s[0] = "good";

    int arr[1000] = {0};
    int tmp[2] = {0};
    int i, k;
    for(i = 0, k = 0; i < len; i++)
    {
        get_2_int(s[i], tmp);
        printf("%d - %d\n", tmp[0], tmp[1]);
        if(tmp[0] == tmp[1])
        {
            arr[k++] = tmp[0];
        }
        else
        {
            arr[k++] = tmp[0];
            arr[k++] = tmp[1];
        }
    }

    for(i = 0; i < k; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    //sorting(arr, k);
    int repeat[100][2] = {0};
    cal_repeat(arr, k, repeat);

    for(i = 0; i < k; i++)
    {
        //if(arr[i] <= threshold)
            printf("%d\n", arr[i]);
    }
}


int main(void)
{
    char *str[] = {"1 2 100", "2 3 100", "4 4 290", "19 2 600"};
    int len = 4;
    int threshold = 7;
    extract_str(str, len, threshold);

    //printf("%s\n", str[0]);
    return 0;
}