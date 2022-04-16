

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
    int i, *pa, a[] = {1, 2, 3, 4, 5};

    pa = a;

    for(i = 0; i <= 9; i++)
    {
        printf("%d\n", *pa);
        pa++;
    }

    return 0;
}