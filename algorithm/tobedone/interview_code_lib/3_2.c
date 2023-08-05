
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

    if(stack_ptr[stack_id] == 1)
    {
        min[stack_id] = data;
    }

    if(data < min[stack_id])
    {
        min[stack_id] = data;
    }

    return 0;
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

    //set min[stack_id]
    int first_idx = 0;
    int last_idx = 0;
    if(min[stack_id] == val)
    {
        /*find the smallest element
            0. if the stack is empty, then return 0.
            1. set the min[stack_id] = first element
            2. for loop: if the following elements less than min[stack_id], then set it to min[stack_id]
        */
        /*
            first element idx: stack_id * stack_size + 1
            last element idx : stack_id * stack_size + stack_ptr[stack_id]
        */

        first_idx = stack_id * stack_size + 1;
        last_idx = stack_id * stack_size + stack_ptr[stack_id];
        min[stack_id] = buff[first_idx];
        for(int i = first_idx; i <= last_idx; i++)
        {
            if(buff[i] < min[stack_id])
            {
                min[stack_id] = buff[i];
            }
        }
    }

    return val;
}

int min_stack(int stack_id)
{
    //check if stack_id is invalid
    if(stack_id < 0 || stack_id > 2)
    {
        printf("stack id is invalid!\n");
        return 2;
    }

    int val = min[stack_id];
    return val;
}


int peek_stack(int stack_id)
{
    int idx = stack_id * stack_size + stack_ptr[stack_id];
    int val = buff[idx];

    printf("stack %d: %d\t", stack_id, val);
    printf("min   %d: %d\n", stack_id, min[stack_id]);
    return val;
}

int main(void)
{
    peek_stack(0);
    push_stack(0, 111);
    push_stack(0, 1);
    peek_stack(0);

    //peek_stack(1);
    //peek_stack(2);
    //pop_stack(0);
    //peek_stack(0);

    return 0;
}