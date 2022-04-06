
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>



/**************************************
                way1
**************************************/

//prepare knowledge
void print_bin(int a)
{
    //int a = 258;
    unsigned char *p1 = (unsigned char *)&a;            //a的首地址，8位。----因为char和unsigned char占用一个字节（8位）
    unsigned char *p2 = (unsigned char *)&a + 1;
    unsigned char *p3 = (unsigned char *)&a + 2;
    unsigned char *p4 = (unsigned char *)&a + 3;

    //printf("%x, %d\r\n", p1, *p1);
    //printf("%x, %d\r\n", p2, *p2);
    //printf("%x, %d\r\n", p3, *p3);
    printf("%x, %d\r\n", p4, *p4);
    printf("%x, %d\r\n", p4 - 1, *(p4 - 1));
    printf("%x, %d\r\n", p4 - 2, *(p4 - 2));
    printf("%x, %d\r\n", p4 - 3, *(p4 - 3));
}


void print_bin_ext(int num)
{
    int i, j, data = 0;
    unsigned char *p = (unsigned char *)&num + 3;     //point to the top memory address of num. (integer uses 4 bytes)
    for(i = 0; i < 4; i++)
    {
        data = *(p - i); //取每个字节的首地址，从高位字节到低位字节，即p p-1 p-2 p-3地址处
        for(j = 7; j >= 0; j--) //处理每个字节的8个位，注意字节内部的二进制数是按照人的习惯存储！
        {
            if(data & (1 << j))//1左移k位，与单前的字节内容j进行或运算，如k=7时，00000000&10000000=0 ->该字节的最高位为0
            {
                printf("1");
            }
            else
            {
               printf("0");
            }
        }
        printf(" ");
    }
    printf("\r\n");
}


/**************************************
                way2
    only works for positive number
**************************************/

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
