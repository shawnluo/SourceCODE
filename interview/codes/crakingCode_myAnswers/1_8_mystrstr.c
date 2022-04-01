#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>

int isSubstring(char *s1, char *s2)
{
    int i, j, tmp;
    int cnt = 0;
    int size1 = strlen(s1);
    int size2 = strlen(s2);

    for(i = 0; i < size1; i++)
    {
        tmp = i;
        for(j = 0; j < size2; j++)
        {
            if((s1[tmp] != '\0') && (s1[i] == s2[j]))
            {
                cnt++;
            }
            else
            {
                cnt = 0;
            }

            if(cnt == size2)
            {
                return 1;
            }
        }
    }

    return 0;
}

int is_rotation(char *s1, char *s2)
{
    int size1 = strlen(s1);
    printf("size1 = %d\n", size1);
    char *p = s1 + 2;
    strcpy(s1 + size1, s1);
    //strcat(s1, s2);

    return isSubstring(s1, s2);
}


char *myStrstr(const char *str, const char *sub)
{
    char *str1 = (char *)str;   //force to char* type for incremental in loop
    char *s1, *s2;

    if(!*sub)   
    {
        return (char *)str;
    }

    while(*str1)
    {
        s1 = str1;
        s2 = (char *)sub;

        while(*s1 && *s2 && (*s1 == *s2))
        {
            ++s1, ++s2;
        }

        if(!*s2)
        {
            return str1;
        }
        ++str1;
    }

    return NULL;
}


int main(void)
{
    //char s1[100] = "show";
    char *s1 = (char *)malloc(100);;
    memset(s1, 0, 100);
    strcpy(s1, "show");

    char s2[] = "hows";

    int ret = is_rotation(s1, s2);
    printf("ret: %d\n", ret);
    return 0;
}