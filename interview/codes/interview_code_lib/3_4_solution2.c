
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

/*
    Hanoi tower play
    1. 3 stacks, 5 numbers
    2. move numbers between stacks
    3. bigger numbers on the bottom
    4. stack push, stack pop

    Move the disks from the first rod to the last rod.
*/


#define DISK 5

#define FROM 0
#define BUFF 1
#define TO 2

int rod[3][DISK] = {0};  //3 rods. buff[0] has 5 disks, buff[1] and buff[2] are empty

int ptr[3] = {-1, -1, -1};  //points to the top stack



/*
    implement push()
    parameters:
        1. rod id: 0, 1, 2
        2. disk size
*/
int push(int rod_id, int disk)
{
    //1. ptr increase
    ptr[rod_id]++;
    int index = ptr[rod_id];
    //printf("index = %d\n", index);
    
    //2. set stack;
    rod[rod_id][index] = disk;
    
    return 0;
}

int pop(int rod_id)
{
    int val = 0;

    int index = ptr[rod_id];
    val = rod[rod_id][index];
    ptr[rod_id]--;

    return val;
}

void peek_ext(int rod_id)
{
    int index = ptr[rod_id];

    if(index == -1)
    {
        printf("peek: rod[%d]: empty!\n", rod_id);
        return;
    }

    printf("peek: rod[%d] \t", rod_id);
    for(int i = 0; i <= index; i++)
    {
        printf("%d ", rod[rod_id][i]);
    }
    printf("\n");
}


/*
                plates          rod_0          rod_1           rod_2
    1. move       n-1        from  : rod_0    to    : rod_1    buffer: rod_2
    2. move       1          from  : rod_0    buffer: rod_1    to    : rod_2
    3. move       n-1        buffer: rod_0    from  : rod_1    to    : rod_2
*/

/*
    3 buffs:
        - from[]
        - buff[]
        - to[]
*/
int Hanoi(int n, int from, int buff, int to)
{
    int val = 0;
    if(1 == n)
    {
        //move 1 disk: from rod_0 to rod_2
        //printf("Move %d:   %d    -->    %d\n", n, from, to);

        val = pop(from);
        push(val, to);
    
        peek_ext(from);
        peek_ext(buff);
        peek_ext(to);
    
        return 0;
    }
    else
    {
        Hanoi(n - 1, from,  to,     buff);
        Hanoi(1,     from,  buff,   to);
        Hanoi(n - 1, buff,  from,   to);
    }

    return 0;
}

int main(void)
{
    push(0, 5);
    push(0, 4);
    push(0, 3);
    push(0, 2);
    push(0, 1);

    peek_ext(0);
    peek_ext(1);
    peek_ext(2);
    printf("-----------------\n");

    Hanoi(DISK, 0, 1, 2);
    return 0;
}