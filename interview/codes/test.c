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
#include <assert.h>


/*
    global:
        buff[]
        size = 100
        stack[3]: [0 ~ 100),  [100, 200), [200, 300)
        pointer to the top of the stack
*/

#define SIZE 100
int buff[SIZE] = {0};
int stack_top = 0;    //point to the top of stack

void push(int data)
{
    int index = stack_top + 1;
    if(index >= SIZE)
    {
        return;
    }
    buff[index] = data;
    stack_top++;
}

int pop()
{
    int value;
    int index = stack_top;
    value = buff[index];

    index = stack_top - 1;
    if(index < 0)
    {
        return -1;
    }
    stack_top--;

    return value;
}

int peek()
{
    int index = stack_top;
    printf("%d\n", buff[index]);
    return buff[index];
}

int isEmpty()
{

}

int isFull()
{

}


int create_stacks()
{

}


int main(void)
{
    push(99);
    push(21);
    push(87);
    int val = peek();
    //printf("%d\n", val);

    pop();
    peek();

    pop();
    peek();

    pop();
    peek();

    pop();
    peek();
    
    return 0;
}