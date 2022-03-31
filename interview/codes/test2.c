

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


void test(float f)
{
    if(f == 0.0)
    {
        printf("%d", 0);
        return;
    }
    /*if(f == 1.0)
    {
        printf("%d", 1);
    }*/

    float data = (f * 2);
    int inc = data >= 1 ? 1 : 0;
    printf("%d", inc);

    data = data >= 1 ? (f * 2) - 1 : (f * 2);
    test(data);
}

int main(void)
{
    float f = 0.4567;
    test(f);


    return 0;
}