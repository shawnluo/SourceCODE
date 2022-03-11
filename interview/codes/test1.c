#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


void showme(void **p, int row, int col)
{
    int (*pArr)[col] = p;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%d ", pArr[i][j]);
        }
        printf("\n");
    }
}

void rotat(int *arr, int row, int col)
{

}

int main()
{
    int arr[3][5] = {   {1, 2, 3, 4, 5},
                        {11, 22, 33, 44, 55},
                        {111, 222, 333, 444, 555}};

    showme(arr, 3, 5);

    rotat(arr, 3, 5);


    return 0;
}