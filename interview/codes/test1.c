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

#define DICT_LEN 256

int *create_delim_dict(char *delim)
{
    int *d = (int *)malloc(sizeof(int) * DICT_LEN);
    memset((void *)d, 0, sizeof(int) * DICT_LEN);

    int i;
    for (i = 0; i < strlen(delim); i++)
    {
        d[delim[i]] = 1;        //set the dict d[] for delim[i] according to it's ASCII
    }
    return d;
}

char *my_strtok(char *str, char *delim)
{
    //assert(str);  //since str may be passed with "NULL", so can NOT assert here!

    //step 0. since strtok can be used in while loop, so we need use static varible
    static char *last, *to_free;
    int *deli_dict = create_delim_dict(delim);

    if (!deli_dict)
    {
        return NULL;
    }

    if (str)
    {
        last = (char *)malloc(strlen(str) + 1);
        if (!last)
        {
            free(deli_dict);
        }
        to_free = last;
        strcpy(last, str);      //malloc last, then copy str to last
    }

   //step 1: pass these characters which match the dict list, also is not the end of string.
    while (deli_dict[*last] && *last != '\0')
    {
        last++;
    }
    str = last;                 
    if (*last == '\0')
    {
        free(deli_dict);
        free(to_free);
        return NULL;
    }

    //step 2: find the character is NOT in the dict list, which need to be return
    while (*last != '\0' && !deli_dict[*last])
    {
        last++;
    }

    //step 3: add '\0' to the end of str, then return it
    *last = '\0';               
    last++;

    free(deli_dict);

    //step 4. return str
    return str;
}

int main()
{
    char * str = "- This, a sample string.";
    char *del = " ,.-";
    char *s = my_strtok(str, del);
    while (s)
    {
        printf("%s\n", s);
        s = my_strtok(NULL, del);
    }
    return 0;
}
