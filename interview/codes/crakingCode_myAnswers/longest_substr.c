#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>



/*
    find the longest substring
    123abcdefa  --> abcdef
*/
char *fnd_sub(char *str)
{
    if(!str)    return NULL;
//    char *s, *s1, *s2;
    int i, j;
    int size = strlen(str);

    static char sub[10] = {0};

    for(i = 1; i < size;i ++)
    {
        for(j = 0; j < i; j++)
        {
            if(str[i] == str[j])
            {
                strcpy(sub, str);
                sub[i] = '\0';
                return sub;
            }
        }
    }
    return str;
}


char *fnd_sub_longest(char *str)
{
    int i, j;
    int size = strlen(str);

    static char sub[10] = {0};
    char *val;
    for(i = 0; i < size - 1; i++)
    {
        str = str + i;
        val = fnd_sub(str);
        //printf("%s\n", val);
        if(strlen(val) > strlen(sub))
            strcpy(sub, val);
    }

    return sub;
}


int main(void)
{
    char *str = "abc123abcdefa";
    //char *ret = fnd_sub_longest(str);

    printf("%s\n", fnd_sub_longest(str));
    //printf("%s\n", fnd_sub_longest(str));
}