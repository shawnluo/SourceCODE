#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define ENABLE_BIT 0x07
#define VOLUME_START_BIT 0x0
#define VOLUME_END_BIT 0x7
bool ControlSound(int Volume, boot Enable)
{
    int i;
    int data = 0;
    int max = ~0;
    int left = 0;
    int right = 0;
    int mask = 0;

    //1. how to access the hardware address?
    //  1). how to access the address 0x80000000
    //2. how to control?
    //  1). set bits
    //  2). clear bits
    int volatile *reg = (int *)0x80000000;

    if(Enable == TRUE)
    {
        *reg |= (1 << ENABLE_BIT);
    }
    else
    {
        /*
            0000    1 << 2     ~100    011
        */
        *reg &= ~(1 << ENABLE_BIT); // 
    }
    
    if((Volume >= 0) && (Volume <= 255))
    {
        //1. set volume bits to 
        data = Volume;


        //0. set the mask to 0x0
        mask = 0;
        //1. clear the bits by "and 0"
        *reg &= ~mask;
        //2. set the data
        *reg |= data;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int main(void)
{
    ControlSound(4, 1); //set volume to 4, enable

    return 0;
}