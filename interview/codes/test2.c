

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


/*
C: Shift Array
View
Try
Insights
Recommended Time: 40 mins
Points: 100
15 test cases (2 samples)
CodingHARDMultithreadingPointersArrays
Rotate an array to the left k times using a pthread and semaphore.



Function Description

Complete the function rotate_by_one in the editor below.

 

rotate_by_one has the following parameters:

    int n[2]: the shape of the array

    struct Student arr[n]: an array of students, see the stub header for a definition of the struct

 

Returns

int[n]: the rotated the array

 
Constraints

1 ≤ n ≤ 100
1 ≤ k ≤ 13
1 ≤ arr[i] ≤ 103

 

Input Format For Custom Testing
The first line contains two space-separated integers n and k.

The second line contains n space-separated integers that represent arr[n].

 

Sample Case 0
Sample Input For Custom Testing

STDIN        Function
-----        --------
5 1          arr size n = 5, k = 1
1 2 3 4 5    arr = [1, 2, 3, 4, 5]
Sample Output

2 3 4 5 1
Explanation

After one rotation the array is [2, 3, 4, 5, 1].

Sample Case 1
Sample Input For Custom Testing

5 4
1 2 3 4 5
Sample Output

2 3 4 5 1
3 4 5 1 2
4 5 1 2 3
5 1 2 3 4
Explanation

After 4 rotations the array is [5, 1, 2, 3, 4].

*/


#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>



#define NUM 5

int index_prod = 0;
int index_cons = 0;

sem_t sem1;
sem_t sem2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *th2(void *arg)
{
    while(1)
    {

        sem_wait(&sem1);       //decrease sem1
        

        pthread_mutex_lock(&mutex);


        pthread_mutex_unlock(&mutex);


        sem_post(&sem2);
        

        sleep(rand() % 3);
    }
}

void *th1(void *arg)
{
    while(1)
    {
        sem_wait(&sem2);


        pthread_mutex_lock(&mutex);



        pthread_mutex_unlock(&mutex);

        sem_post(&sem1);

        sleep(rand() % 3);
    }
}

int main(int argc, char *argv[])
{
    pthread_t pid, cid;

    sem_init(&sem1, 0, NUM);
    sem_init(&sem2, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pid, NULL, th1, NULL);
    pthread_create(&cid, NULL, th2, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

int volatile *reg = (int *)0x80000000;
#define REG_CTL (*(volatile unsigned long*)0x80000000)

REG_CTL |= (1 << 0x7);

int i = 1;
char *p = (char *)&i;
if(*p == 1) return 1;
else        return 0;

char *p = (char *)&i;

#define REG_CTL (*volitle unsigned long*)0x80000000

REG_CTL |= (1 << 0x7)

for(int i = 8; i <= 15; i++)
{
    data |= (input >> i);
    data <<= 1;
}

SOUND_CTL |= (data << 7);


//1. set mask   1111... 00 1111...
    //a. max = ~0
    //b. left = max - ((1 << i) - 1)
    //c. right = (1 << j) - 1
    //d. mask = left | right
//2. *reg = *reg & mask;
//3. *reg = *reg | data;
    //a. data <<= 


int power(int base, int n)
{
    if(n == 0)  return 1;
    return base * power(base, n - 1);
}