
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


#define s1 0
#define s2 1

int s[2][5] = {{0, 120, 54, 5, 98}, {0}};

int ptr[2] = {-1, -1};


void push(int id, int data)   //id is stack id
{
    int index = ptr[id] + 1;
    ptr[id]++;
    s[id][index] = data;
}

int pop(int id)
{
    int val = 0;
    int index = ptr[id];
    val = s[id][index];
    ptr[id]--;

    return val;
}

int peek(int id)
{
    int val = 0;
    int index = ptr[id];
    val = s[id][index];
    return val;
}

int isEmpty(int id)
{
    return ptr[id] == -1 ? 1 : 0;
}


int main(void)
{
    /*strategy:
        find the smallest element, and push it to stack[1]

        1. pop stack[0], save it to tmp;
        2. compare tmp to stack[1], if tmp < stack[1], then pop stack[1] and push to stack[0]
        3. push tmp to stack[1]
    */

   while(!isEmpty(s1))  //if s1 is NOT empty
   {
       int tmp = pop(s1);
       //if s2 is NOT empty, and s2 larger than tmp
       while(!isEmpty(s2) && peek(s2) > tmp)
       {
           //then pop(s2), and push to s1
           push(s1, pop(s2));
       }
       //now tmp is the samllest, push to s2
       push(s2, tmp);
   }

   printf("%d ", peek(s2));

   pop(s2);
   printf("%d ", peek(s2));

   pop(s2);
   printf("%d ", peek(s2));

   pop(s2);
   printf("%d ", peek(s2));

   pop(s2);
   printf("%d\n", peek(s2));

    return 0;
}