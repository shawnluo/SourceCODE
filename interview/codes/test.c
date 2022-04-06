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

sem_t sem1;
sem_t sem2;

pthread_mutex_t mutex;

void *th1(void *arg)
{


}

int main()
{
    sem_init(&sem1, 0, 2);
    sem_init(&sem2, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&pid, NULL, th1, NULL);
    pthread_create(&cid, NULL, th2, NULL);
    
    return 0;
}