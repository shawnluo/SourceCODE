#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t write_mutex;

void *my_write(void *temp) 
{
    char *ret;
    char str[100] = {0};

    while(1)
    {
        pthread_mutex_lock(&write_mutex);
        printf("1 - LOCK\n");

        while(1)
        {
            scanf("%s", str);
            if(strcmp(str, "t1") == 0)
            {
                printf("1 - got ok!\n");
                break;
            }
            sleep(1);
        }

        pthread_mutex_unlock(&write_mutex);
        printf("1 - Unlocked\n");
        memset(str, 0, 100);
        sleep(2);
    }
    return ret;
}


void *my_read(void *temp) 
{
    char *ret;
    char str[100] = {0};

    while(1)
    {
        pthread_mutex_lock(&write_mutex);
        printf("2 - LOCK\n");
        while(1)
        {
            scanf("%s", str);
            if(strcmp(str, "t2") == 0)
            {
                printf("2 - got ok!\n");
                break;
            }
            sleep(1);
        }

        pthread_mutex_unlock(&write_mutex);
        printf("2 - Unlocked\n");
        sleep(2);
    }
    return ret;
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