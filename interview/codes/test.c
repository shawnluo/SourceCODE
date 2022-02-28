
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
int stack_id = 0;   //0, 1, 2
int stack_size = 300;
int stack_ptr[3] = {0, 0, 0};
int min[3] = {0, 0, 0};

int push_stack(int stack_id, int data)
{
    //1. check if stack is full
    if(stack_ptr[stack_id] >= 299)
    {
        printf("stack is full!\n");
        return 1;
    }
    //2. check if stack_id is invalid
    if(stack_id < 0 || stack_id > 2)
    {
        printf("stack id is invalid!\n");
        return 2;
    }

    int idx = stack_id * stack_size + stack_ptr[stack_id] + 1;
    buff[idx] = data;
    stack_ptr[stack_id]++;

    if(data < min[stack_id])
    {
        min[stack_id] = data;
    }

    return 0;
}

int min_stack(int stack_id)
{
    //check if stack_id is invalid
    if(stack_id < 0 || stack_id > 2)
    {
        printf("stack id is invalid!\n");
        return 2;
    }

    int idx_btm = stack_id * stack_size + stack_ptr[0];


    int val = min[stack_id];
    return val;
}

int pop_stack(int stack_id)
{
    //1. check if stack is empty
    if(stack_ptr[stack_id] <= 0)
    {
        printf("stack is empty!\n");
        return 1;
    }
    //2. check if stack_id is invalid
    if(stack_id < 0 || stack_id > 2)
    {
        printf("stack id is invalid!\n");
        return 2;
    }

    int idx = stack_id *stack_size + stack_ptr[stack_id];
    int val = buff[idx];

    buff[idx] = 0;          //set 0 to the stack
    stack_ptr[stack_id]--;  //decrease stack pointer

    if(min[stack_id] > val)
    {
        for(int i = 0; i < idx - 1; i++)
        {
            if(buf[i] < val)    break;
            else
            {
                buff[]
            }
        }

    }


    return val;
}

int peek_stack(int stack_id)
{
    int idx = stack_id * stack_size + stack_ptr[stack_id];
    int val = buff[idx];

    printf("stack %d: %d\n", stack_id, val);
    return val;
}

int main(void)
{
    push_stack(0, 1000);
    push_stack(1, 100);

    peek_stack(0);
    peek_stack(1);
    peek_stack(2);

    pop_stack(1);
    peek_stack(0);
    peek_stack(1);
    peek_stack(2);

    return 0;
}