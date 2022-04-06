

#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>

/*
    1. sort every element
    2. sort array
*/

void sort_string(char str[])
{
    int i, j;
    int size = strlen(str);
    // printf("size = %d\n", size);
    // printf("%s\n", str);
    char tmp;

#if 1
    for(i = 0; i < size; i++)
    {
        for(j = 1; j < size - i; j++)
        {
            //printf("%c, %c\n", str[j], str[j + 1]);
            if(str[j - 1] > str[j])
            {
                tmp = str[j - 1];
                str[j - 1] = str[j];
                str[j] = tmp;
            }
        }
    }
#else
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (str[i] > str[j])
            {
                tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
        }
    }
#endif

    //printf("%s\n", str);
}

void sortAll(char str[6][10], int size)
{
    char tmp[50];
    for(int i = 0; i < 6; i++)
    {
        sort_string(str[i]);
    }
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(strcmp(str[i], str[j]) > 0)
            {
                strcpy(tmp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], tmp);
            }
        }
    }
}

int main(void)
{
    char str[6][10] = {"show", "me", "owhs", "good", "em", "hwos"};

    //sort_string(str[0]);
    //printf("%s\n", str[0]);

    sortAll(str, 6);
    for(int i = 0; i < 6; i++)
    {
        printf("%s ", str[i]);
    }
    printf("\n");

    return 0;
}