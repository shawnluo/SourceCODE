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


char save[100];
/*
    find the longest substring
    123abcdefa  --> abcdef
*/
char *longest_from_head_1(char *str)
{
    if(!str)    return NULL;
//    char *s, *s1, *s2;
    int i, j;
    int size = strlen(str);

    static char sub[10] = {0};  //also can use malloc

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


/*
    bruteforce 2
    using hash[] to check if it's unique
*/
char *longest_from_head_2(char *str)
{
    int i, j;
    int len = strlen(str);
    char hash[256] = {0};
    strcpy(save, str);

    for(i = 0 ; i < len; i++)
    {
        if(hash[*(str + i)] == 0)
            hash[*(str + i)] = 1;
        else
        {
            save[i] = '\0';
            //printf("save: %s\n", save);
            return save;
        }
    }
    return save;
}


char *fnd_sub_longest(char *str)
{
    int i, j;
    int size = strlen(str);

    static char sub[100] = {0};  //or using malloc
    char *val;
    for(i = 0; i < size; i++)
    {
        str = str + i;
        val = longest_from_head_1(str);
        //printf("%s\n", val);
        if(strlen(val) > strlen(sub))
            strcpy(sub, val);
    }

    return sub;
}


//return the repeat char position
int longest_from_head_3(char *str)
{
    if(!str)    return NULL;
//    char *s, *s1, *s2;
    int i, j;
    int size = strlen(str);

    //static char sub[10] = {0};  //also can use malloc

    for(i = 1; i < size;i ++)
    {
        for(j = 0; j < i; j++)
        {
            if(str[i] == str[j])
            {
                //strcpy(sub, str);
                //sub[i] = '\0';
                return j;
            }
        }
    }
    return size;
}

/*
    sliding windows:
    1. start from the first char, to find the repeat char;
    2. find the repeat char, then start from the next char to call STEP1
*/
char *fnd_sub_longest_2(char *str)
{
    int i, j, val = 0;
    int len = strlen(str);
    int max_len = 0;
    int start = 0;
    for(i = 0; i < len; i++)
    {
        if(i == 0)
        {
            val = longest_from_head_3(str);
            printf("1 - val = %d\n", val);
            //max_len = (val - start + 1) > max_len ? (val - start) : max_len;
            strncpy(save, str + val, );

            if(val == (len - 1))
                break;
        }
        else
        {
            start = val + i + 1;
            printf("s: %s\n", str + start);
            val = longest_from_head_3(str + start);
            printf("2 - val = %d\n", val);

            max_len = (val - start + 1) > max_len ? (val - start) : max_len;
            
            if(val == (len - 1))
                break;
        }
        //printf("max_len = %d\n", max_len);
    }

    return NULL;
}


int main(void)
{
    char *str = "abc123abcdefa";
    fnd_sub_longest_2(str);

    //printf("%s\n", fnd_sub_longest(str));
    //printf("%s\n", fnd_sub_longest(str));
}