
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#if 1
/*
    Hanoi tower play
    1. 3 stacks, 5 numbers
    2. move numbers between stacks
    3. bigger numbers on the bottom
    4. stack push, stack pop

    Move the disks from the first rod to the last rod.
*/

#define ROD 3
#define DISK 5

#define FROM 0
#define BUF 1
#define TO 2

int rod[3][DISK] = {0};  //3 rods. buff[0] has 5 disks, buff[1] and buff[2] are empty

/*
    implement push()
    parameters:
        1. rod id
        2. disk size
*/
int push(int rod, int disk)
{
    //set disk position which push to the rod.
    
    //1. if disk size larger than the buff[rod], then return fail
    if(disk > buff[rod][idx])   //rod: the rod. idx: the top plate on rod
    {
        return -1;
    }

    int index = 
}
#endif

/*
                plates          rod_0          rod_1           rod_2
    1. move       n-1        from  : rod_0    to    : rod_1    buffer: rod_2
    2. move       1          from  : rod_0    buffer: rod_1    to    : rod_2
    3. move       n-1        buffer: rod_0    from  : rod_1    to    : rod_2
*/

/*
    3 buffs:
        - buff[from]
        - buff[buffer]
        - buff[to]
*/
int Hanoi(int n, int from, int buffer, int to)
{
    if(1 == n)
    {
        //move 1 disk: from rod_0 to rod_2
        printf("Move %d:   %d    -->    %d\n", n, from, to);

        //from: buff
        push(n, from[], to);
        pop();
        peek();

        return 0;
    }
    else
    {
        Hanoi(n - 1, rod[FROM],    rod[TO],    rod[BUF]);
        Hanoi(1,     rod[FROM] ,  rod[BUF], rod[TO]);
        Hanoi(n - 1, buffer, from, to);
    }

    return 0;
}

int main(void)
{
    Hanoi(5, 0, 1, 2);
    return 0;
}