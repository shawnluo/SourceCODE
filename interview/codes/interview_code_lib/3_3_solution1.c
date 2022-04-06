
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
    1. set up 3 stacks,
    2. each stack size set to 100
    3. set stack ptr to point to the stack
*/

#define SIZE 5

int stack[3][SIZE] = {0};
int stack_full_size = 300;
int stack_size = 100;   //for each container: [0, 99] [100, 199], [200, 299]
int stack_ptr = -1;     // ptr == - 1, then no data in the stack

/*
    1. check the stack ptr:
        a. ptr > 0   && ptr <= 100, then save data to stack[0]
        b. ptr > 100 && ptr <= 200, then save data to stack[1]
        c. ptr > 200 && ptr <= 200, then save data to stack[2]
*/
int push_stack(int data)
{
    //1. check if stack is full
    if(stack_ptr == 300)
    {
        printf("stack is full!\n");
        return 1;
    }
    
    //2. set which substack saves the data 
    int stack_id = 0;       //container id
    int stack_index = 0;    //postion in container

    stack_ptr++;

    stack_id = stack_ptr / SIZE;
    stack_index = stack_ptr % SIZE;

    stack[stack_id][stack_index] = data;

    return 0;
}


int pop_stack()
{
    //1. check if stack is empty
    if(stack_ptr == -1)
    {
        printf("stack is empty!\n");
        return 1;
    }

    //2. check which sub stack
    int stack_id = 0;       //container id
    int stack_index = 0;    //postion in container
    stack_id = stack_ptr / SIZE;
    stack_index = stack_ptr % SIZE;

    int val = stack[stack_id][stack_index]; //locate the ptr
    stack[stack_id][stack_index] = 0;       //set 0 to the stack
    
    stack_ptr--;  //decrease stack pointer

    return val;
}


//TODO
int peek_stack()
{
    int stack_id = 0;    //postion in container
    int stack_index = 0;    //postion in container
    stack_id = stack_ptr / SIZE;
    stack_index = stack_ptr % SIZE;

    int val = stack[stack_id][stack_index]; //locate the ptr

    printf("peek: %d\n", val);

    return val;
}


int main(void)
{
    push_stack(111);
    push_stack(222);
    push_stack(333);
    push_stack(444);
    push_stack(555);
    push_stack(666);

    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    pop_stack();
    peek_stack();

    //peek_stack(1);
    //peek_stack(2);
    //pop_stack(0);
    //peek_stack(0);

    return 0;
}