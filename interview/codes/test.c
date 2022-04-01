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

void swap(char *x, char *y)
{
    char c = *x;
    *x = *y;
    *y = c;
}

//sorting
void sort(char *str)
{
    int i, j;
    int size = strlen(str);

    for(i = 0; i < size; i++)
    {
        for(j = 1; j < size - i; j++)
        {
            if(str[j - 1] > str[j])
            {
                swap(str + j - 1, str + j);
            }
        }
    }
}

int main(void)
{
    char str[] = "abclkjjmm3421";

    sort(str);
    printf("%s\n", str);

    return 0;
}




void *my_memcpy(void *des, void *src, unsigned int len)
{
    assert(des);
    assert(src);
    if(des == src)
        return src;

    if(des > src)   //copy from end
    {

    }
    else
    {
        while(len--)
        {
            *des++ = *src++;
        }
    }

}