
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

int **stack = NULL;
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
    //1. check if the stack is empty
    if(stack == NULL)
    {
        return -1;
    }

    //2. check if stack is full
    if(stack_ptr == stack_full_size)
    {
        printf("stack is full!\n");
        return 1;
    }
    
    //3. set which substack saves the data 
    int stack_id = 0;       //container id
    int stack_index = 0;    //postion in container

    stack_ptr++; //

    stack_id = stack_ptr / SIZE;
    stack_index = stack_ptr % SIZE;

    if(stack[stack_id] == NULL)
    {
        stack[stack_id] = (int *)malloc(sizeof(int) * stack_size);
        memset(stack[stack_id], 0, sizeof(int) * stack_size);
    }
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


int peek_stack()
{
    int stack_id = 0;    //postion in container
    int stack_index = 0;    //postion in container
    stack_id = stack_ptr / SIZE;
    stack_index = stack_ptr % SIZE;

    if(stack[stack_id] == NULL || stack_ptr == -1)
    {
        printf("the stack is empty!\n");
        return -1;
    }

    int val = stack[stack_id][stack_index]; //locate the ptr

    printf("peek: %d\n", val);

    return val;
}

int init_stack()
{
    stack = (int **)malloc(sizeof(int *) * SIZE);
    if(stack == NULL)
    {
        return -1;
    }
    memset(stack, 0, sizeof(int *) * SIZE);

    return 0;
}

int free_stack()
{
    int n = stack_full_size / stack_size;
    for(int i = 0; i <= n; i++)
    {
        if(stack[i] != NULL)
        {
            free(stack[i]);
        }
    }
    free(stack);

    return 0;
}


int main(void)
{
    init_stack();

    peek_stack();

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

    free_stack();

    return 0;
}