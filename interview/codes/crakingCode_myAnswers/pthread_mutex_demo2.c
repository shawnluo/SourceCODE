#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t write_mutex;

void print_cnt(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
}

void *my_write(void *temp) 
{
    //char *ret;
    //char str[100] = {0};

    pthread_mutex_lock(&write_mutex);
    print_cnt(1000);
    pthread_mutex_unlock(&write_mutex);

    //return ret;
}


void *my_read(void *temp) 
{
    //char *ret;
    //char str[100] = {0};

    pthread_mutex_lock(&write_mutex);
    print_cnt(1000);
    pthread_mutex_unlock(&write_mutex);

    //return ret;
}


int main(void) 
{
    pthread_t thread_id,thread_id1;
    pthread_attr_t attr;
    int ret;
    void *res;

    ret=pthread_create(&thread_id,NULL,&my_write,NULL);
    ret=pthread_create(&thread_id1,NULL,&my_read,NULL);

    pthread_join(thread_id,&res);
    pthread_join(thread_id1,&res);

    return 0;
}