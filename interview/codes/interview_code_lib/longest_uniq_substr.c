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

    static char sub[10] = {0};  //or using malloc
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


/*
    slide window:
    right: to track the repeated char
    left:  to move 
*/
int longest_uniq_sub(char *s) {
    int left = 0;
    int right = 0;
    int res = 0;
    int len = strlen(s);
    char hash[128] = {0};
    
    while(right < len) {
        hash[s[right]]++;

        while(hash[s[right]] > 1) {
            hash[s[left]]--;
            left++;                     //beautiful.
        }
        int len_uniq = right - left + 1;
        res = res > len_uniq ? res : len_uniq;
        right++;
    }
    return res;
}


int main(void)
{
    char *str = "abc123abcdefa";
    //char *ret = fnd_sub_longest(str);

    printf("%s\n", fnd_sub_longest(str));
    //printf("%s\n", fnd_sub_longest(str));
}