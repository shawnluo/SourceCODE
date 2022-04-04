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

/*longest common substring
1. brutal
    s1 as a string
    
    s2 from head to tail. list all the substring of s1. cmp and save the longest one
        step 1. find the longest one from s1 head;
        step 2. s1 move from head to tail, call step1
*/



char *longest_substr(char *s1, char *s2)
{
    char *longest = (char *)malloc(100);
    memset(longest, 0, 100);

    int i, j, k;
    int size1 = strlen(s1);
    int size2 = strlen(s2);
    for(i = 0; i < size1; i++)
    {
        k = i;
        for(j = 0; j < size2; j++)
        {
            if(s1[i] != s2[j])
            {
                if()
                strcpy()
            }
        }
    }
    
    
}

int main(void)
{
    char *s1 = "abcdef";
    char *s2 = "cdabce";
    char *s = longest(s1, s2);

    printf("%s\n", s);

    return 0;
}