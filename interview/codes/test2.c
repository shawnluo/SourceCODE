

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


int main(void)
{
    char str[100] = "abcdefg";
    char newStr[100] = {0};

    printf("%s\n", newStr);

    strcat(newStr, str);
    printf("%s\n", newStr);

        strcat(newStr, str);
    printf("%s\n", newStr);

    return 0;
}