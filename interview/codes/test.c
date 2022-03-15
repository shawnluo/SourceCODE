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

/*
    producer and consumer:
    1. buffer[10]
    2. producer pushes to buffer
    3. consumer pops from buffer
    4. producer pauses pushing when buffer is full
    5. consumer pauses popping when buffer is empty

    solution:
        1. mutex for 2 threads to access the same buffer
        2. synchnization of produce and consume
            full    0
            avail   N - the empty unit number
*/

#define N 5
#define FIFO "myfifo"

time_t end_time;
int fd;
char buf_r[100];
sem_t mutex, avail, full;

void productor(void *arg);
void consumer(void *arg);

int main(void)
{
    pthread_t id1, id2;
    end_time = time(NULL) + 30;
    int ret;

    if((mkfifo(FIFO, 0666) < 0) && (errno != EEXIST))
    {
        printf("cannot create fifoserver\n");
    }
    printf("Preparing for reading bytes...\n");
    memset(buf_r, 0, sizeof(buf_r));

    fd = open(FIFO, O_RDWR|O_NONBLOCK, 0);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    ret = sem_init(&mutex, 0, 1);
    ret = sem_init(&avail, 0, N);   //N empty space
    ret = sem_init(&full, 0, 0);
    if(ret != 0)
    {
        perror("sem_init");
    }

    ret = pthread_create(&id1, NULL, (void *)productor, NULL);
    if(ret != 0)
    {
        perror("pthread cread1");
    }
    ret = pthread_create(&id2, NULL, (void *)consumer, NULL);
    if(ret != 0)
    {
        perror("pthread cread2");
    }

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    return (0);
}

void productor(void *arg)
{
    int i, nwrite, val;
    while(time(NULL) < end_time)
    {
        sem_wait(&avail);   //N empty space
        sem_getvalue(&avail, &val);
        printf("p - %d\n", val);

        sem_wait(&mutex);   //it does NOT matter which thread go first

        if((nwrite = write(fd, "hello", 5)) == -1)
        {
            printf("write fail, data unavailable!\n");
        }
        else
        {
            sleep(1);
            printf("write hello to the FIFO. buf remain: %d\n", strlen(buf_r));
        }
        sem_post(&full);
        sem_post(&mutex);
        sleep(1);
    }
}

void consumer(void *arg)
{
    int nolock = 0;
    int ret, nread, val;
    int n = 1;
    while(time(NULL) < end_time)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        sem_getvalue(&avail, &val);
        printf("c - %d\n", val);

        memset(buf_r, 0, sizeof(buf_r));
        if((nread = read(fd, buf_r, n)) == -1)
        {
            printf("no data yet\n");
        }
        sleep(3);
        printf("read %s from FIFO, remain: %d\n", buf_r, strlen(buf_r));

        sem_post(&avail);
        sem_post(&mutex);
        sleep(1);
    }
}