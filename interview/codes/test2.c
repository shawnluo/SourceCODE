#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
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

int main(void)
{
    char *s = "abcdef";
    char str[100] = {0};
    strcpy(str, s);
    printf("%s\n", str);

    char *s2 = "11234567";
    strncpy(str, s2, 2);
    printf("%s\n", str);

    return 0;
}