
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

/*
    one single array for 3 stacks
    parameters:
        1. int buf[900]:    is the stack container
        2. int stack_id: 3 stacks from 0 to 2
        3. int stack_size: 300
        4. int stack_ptr[3]: 3 stack pointers, for pointing to the stack top
*/

int buff[900] = {0};
int buff_min[900] = {0};
int id = 0;   //0, 1, 2
int size = 300;
int ptr = 0;
int ptr_min = 0;

//handle mini element
//always save the minimal element
//if push data > minimal stack, then instead of pushing data, push the minimal element

int isFull() {
    if(ptr == size) {
        return 1;
    } else {
        return 0;
    }
}

int isEmpty() {
    if(ptr == 0) {
        return 1;
    } else {
        return 0;
    }
}

int push_stack(int data)
{
    //1. check if stack is full
    if(isFull) {
        return -1;
    }

    buff[++ptr] = data;

    if(data > buff_min[ptr_min])
    {
        buff_min[ptr_min + 1] = buff_min[ptr_min];
        ptr_min++;
    }

    if(data < buff_min[ptr_min])
    {
        buff_min[ptr_min] = data;
    }

    return 0;
}


int pop_stack()
{
    //1. check if stack is empty
    if(isEmpty())
    {
        printf("stack is empty!\n");
        return -1;
    };

    int ret = buff[ptr];
    ptr--;  //decrease stack pointer
    ptr_min--;

    return ret;
}



int peek_stack()
{
    int val = buff[ptr];
    return val;
}

int main(void)
{
    int min;
    
    peek_stack();
    min = buff_min[ptr_min];
    
    push_stack(111);
    min = buff_min[ptr_min];
    
    push_stack(1);
    min = buff_min[ptr_min];

    peek_stack();

    return 0;
}