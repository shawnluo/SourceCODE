#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


void showme(void *p, int row, int col)
{
    int (*pArr)[col] = p;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%d\t", pArr[i][j]);
        }
        printf("\n");
    }
}

void showme_2(int **arr, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%5d\t", arr[i][j]);
        }
    }
}

void rotat(void *p, int row, int col)
{
#if 1
    int (*arr)[col] = p;
    int i, j, tmp;
    for(i = 0; i < row; i++)
    {
        for(j = i; j < col; j++)
        {
            tmp = arr[j][i];
            arr[j][i] = arr[i][j];
            arr[i][j] = tmp;
        }
    }
#endif
}

void rotat2(void *p, int size)
{
    int tmp;
    int (*arr)[size] = p;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size / 2; j++)
        {
            tmp = arr[i][j];
            arr[i][j] = arr[i][size - j];
            arr[i][size - j] = tmp;
        }
    }
}


int main()
{
#if 0
    int m = 5;
    int n = 5;
    int arr[5][5] = {   {1, 2, 3, 4, 5},
                        {11, 22, 33, 44, 55},
                        {111, 222, 333, 444, 555},
                        {1111, 2222, 3333, 4444, 5555},
                        {11111, 22222, 33333, 44444, 55555}};
#else
    int m = 5;
    int n = 5;
 
     int arr[5][5] = {   {1, 2, 3, 4, 5},
                        {11, 22, 33, 44, 55},
                        {111, 222, 333, 444, 555},
                        {1111, 2222, 3333, 4444, 5555},
                        {11111, 22222, 33333, 44444, 55555}};
    // dynamically create an array of pointers of size `m`
    int **pArr = (int **)malloc(m * sizeof(int *));
 
    // dynamically allocate memory of size `n` for each row
    for (int r = 0; r < m; r++) {
        pArr[r] = (int *)calloc(n, sizeof(int));
        pArr[r] = arr[r];
    }

 #endif
    //showme(arr, m, n);
    //showme_2(arr, 5, 5);

    rotat(arr, 5, 5);
    showme(arr, 5, 5);
    rotat2(arr, 5);
    showme(arr, 5, 5);

    return 0;
}