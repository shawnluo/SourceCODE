
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


void showme(void *p, int row, int col)
{
    int (*pArr)[col] = p;

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%d ", (*pArr)[j]);
        }
        pArr++;
        printf("\n");
    }
}

/*          bit manipulation
    1. print_bin
    2. get max integer?
    3. set 1 bit?     *reg |= 1;
    4. clear 1 bit?   *reg &= ~1;
    5. set registar i ~ j bits to data
        1). get mask:
            a. get max integer, all bits are 1. MAX_INT or ~0
            b. get high, [max, high) are 1s, [high, 0] are 0s.
            c. get low, (low, 0] are 1s.
            d. mask = high | low 
        3). clear i ~ j bits:    data &= mask
        4). data << low
        5). *reg | data
    6. volatile for register
*/

//int len = 0;

void print_bin(int n, int *arr, int *len)
{
    //static int len = 0;
    if(n > 0)
    {
        print_bin(n / 2, arr, len);
    }
    else
    {
        return;
    }

    arr[*len] = n % 2;
    *len = *len + 1;
    n = n % 2;
    
    //printf("%d, %d\n", n, i++);
    //push(n % 2);
}


int main()
{
    int arr[10] = {0};
    int len = 0;

    print_bin(8, arr, &len);

    printf("%d\n", len);
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
