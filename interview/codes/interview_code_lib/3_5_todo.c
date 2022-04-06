
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
    implement a queue using 2 stacks

    queue: 
    1. first in, first served
    2. served, then delete

        first     last
                    a, b, c, d, e    increase
    then
        decrease    b, c, d, e, f

    2 ptr: first one points to the early one; another points to last.
*/

//    solution
//1. define a stack[1] for push/increase 
//2. define a stack[0] for pop
//3. if stack_pop[] is empty, then stack_push[] pop and stack_pop push

int ptr[2] = {-1, -1};  //ptr points to the stack top
int stack[2] = {0};     //stack[0]: pop, stack[1]: push



void MyQueue_write(int data)
{
    push(data, stack[1]);
}


//pop
int MyQueue_read()
{
    int val;
    if(ptr[0] != -1)
    {
        return pop(stack[0]);
    }

    //if stack[0] is empty, then pop stack[1]
    for(int i = 0; i <= ptr[1]; i++)
    {
        val = pop(stack[1]);
        push(val);
    }
    
    val = pop(stack[0]);

    return val;
}

void MyQueue_peek()
{

}

int isEmpty(int stack_id)
{

}

int main(void)
{
    int val;
    MyQueue_write(100);
    val = MyQueue_read();
    MyQueue_peek();

    return 0;
}