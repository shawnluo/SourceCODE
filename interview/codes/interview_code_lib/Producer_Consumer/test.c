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
    1. set a circular queue as a warehouse to store the product
        1). queue[i] = data
        2). i = (i + 1) % NUM
    2. 1 thread to produce product and install it to the queue
    3. another thread to consume the product from the queue
*/

#define NUM 5
int queue[NUM];     //circular queue
int index_prod = 0; //index queue for product
int index_cons = 0; //index queue for consumer

sem_t blank_num;    //number of empty space in the queue
sem_t prod_num;     //number of product in the queue

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg)
{
    while(1)
    {
        //step1:
        //  if queue has space to push(blank_num == 0), then enter and decrease blank_num by 1
        //  else, then block here untile blank_num >0
        sem_wait(&blank_num);       //decrease blank_num
        
        //step2:
        //  protect the following code, without be interrupted
        //  get the mutex lock, if it's unavailable, then block here.
        //  so only 1 thread can produce or consume at the same time
        pthread_mutex_lock(&mutex);

        //step3:
        //  set queue data
        //  data need to pushed as circular queue data structure
        int data = random() % 1000;
        queue[index_prod] = data;
        index_prod = (index_prod + 1) % NUM;
        
        //step4:
        //  unlock the mutex, so consumer thread can start to run
        pthread_mutex_unlock(&mutex);

        //step5:
        //  signal prod_num to increase by 1
        sem_post(&prod_num);
        
        printf("- P -");
        for(int i = 0; i < NUM; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");
        sleep(rand() % 3);
    }
}

void *consumer(void *arg)
{
    while(1)
    {
        //step1:
        //  if the queue has product to consume, then enter, and decrease the prod_num by 1
        //  else then block here
        sem_wait(&prod_num);

        //step2:
        //  protect the following code, without be interruptd
        pthread_mutex_lock(&mutex);

        //step3:
        //  consume the data
        queue[index_cons] = 0;
        index_cons = (index_cons + 1) % NUM;

        //step4:
        //  unlock mutex
        pthread_mutex_unlock(&mutex);

        //step5:
        //  signal blank_num
        sem_post(&blank_num);

        printf("- C -");
        for(int i = 0; i < NUM; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");

        sleep(rand() % 3);
    }
}

int main(int argc, char *argv[])
{
    pthread_t pid, cid;

    sem_init(&blank_num, 0, NUM);
    sem_init(&prod_num, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    sem_destroy(&blank_num);
    sem_destroy(&prod_num);

    return 0;
}