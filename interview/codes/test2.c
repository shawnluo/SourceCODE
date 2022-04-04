

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
    1234
    - 1 12 123 1234
    - 2 23 234
    - 3 34
    - 4
*/


void print_str(const char *str, char *substr, int pos, int num)
{
    int i = 0;
    while(num--)
    {
        //printf("%c", str[pos++]);
        substr[i++] = str[pos++];
    }
    substr[i] = '\0';
}


// Is substr str's substring?
//("322342es", "234")
int Is_substr(const char *str, const char *sub)
{
    const char *pStr;
    const char *pSub = sub;

    int len = strlen(sub);
    int match = 0;

    //for(p1 = str; *p1 != '\0'; p1++)
    while(*str != '\0')
    {
        pStr = str;
        for(pSub = sub; *pSub != '\0'; pSub++)
        {
            if(*pStr == *pSub)
            {
                pStr++;
                match++;
                if(match == len)
                {
                    return 0;
                }
                //printf("match = %d\n", match);
            }
            else
            {
                match = 0;
                break;
            }
        }
        str++;
    }

    return -1;
}


void set_longest_substr(char *str, char *longest_substr)
{
    //printf("a - %s - %s\n", str, longest_substr);
    strcpy(longest_substr, str);
    //printf("b - %s - %s\n", str, longest_substr);
}


void list_substr(const char *str, const char *str2)
{
    int pos, num;
    int len = strlen(str);
    char substr[100] = {0};
    //char *str2 = "123";
    char longest_substr[100];

    for(pos = 0; pos < len; pos++)  // print from
    {
        for(num = 1; num <= len - pos; num++)  // print how many char
        {
            print_str(str, substr, pos, num);

            //printf("%s - %s\n", str2, substr);
            if(Is_substr(str2, substr) == 0)
            {
                if(strlen(substr) > strlen(longest_substr))
                {
                    set_longest_substr(substr, longest_substr);
                }
            }

            memset(substr, 0, 100);
        }
        //printf("\n");

    }
    printf("longest: %s\n", longest_substr);
}


int main(void)
{
    const char *str = "1234abcdef2345";
    const char *str2 = "322342abcdefes";
    list_substr(str, str2);
    
    //int ret = Is_substr("322342es", "234");
    //printf("ret = %d\n", ret);

    return 0;
}