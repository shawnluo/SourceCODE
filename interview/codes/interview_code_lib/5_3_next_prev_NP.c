#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>


int cal_bits(int n)
{
    int cnt = 0;
    while(n >= 0)
    {
        if(n & 1)   ++cnt;
        n >= 1;
    }
    return cnt;
}

/*
    set n, index bit to true
*/
int setBit(int n, int index, boolean b)
{
    int mask;
    if (b)
    {
        mask = 1 << index;
        n = n | mask;
    }
    else
    {
        mask = ~(1 << index);
        n = n & mask;
    }
    return n;
}

/*
    get n, index bit value
*/
int getBit(int n, int index)
    return  ((n & (1 << index)) > 0);

/*
    get previous smalest number which has same number of 1 
    1. find the first 0 from bit            - A
    2. find the first 1 after the first 0   - B
    3. clear B, 
    4. set the 0 bit before B(may not be A)

*/
int getPrev_NP(int n)
{
    int index = 0;
    int cntZeros = 0;

    //1. find the first 0 from right end
    while(getBit(n, index))     index++;

    //2. find the first 1 after first 0
    while(!getBit(n, index))
    {
        index++;
        cntZeros++;
    }

    //3. set the first 1 bit to 0
    setBit(n, index, false);

    //4. set the previous 0 bit to 1(may not be the one after first while loop)
    setBit(n, --index, true);
    cntZeros--;

    //5. set the bits before the step 2 [index - 1, cntZeros]
    for(int i = index - 1; i >= cntZeros; i--)  n = setBit(n, i, true);

    //6. clear the bits [countZero, 0]
    for(int i = cntZeros - 1; i >= 0; i--)  n = setBit(n, i, false);

    return n;
}

int getNext_NP(int n)
{

}

int main(void)
{
    int val;
    val = getPrev_NP();
    printf("%d\n", val);

    return 0;
}