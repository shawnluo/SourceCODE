
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


void showme(int (*arr)[3], int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void showme_ext(void *arr, int n)
{
    int i, j;
    int (*s)[n] = arr;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", s[i][j]);
        }
        printf("\n");
    }
}

void rotate(int arr[][3], int size)
{
    if(!arr)
    {
        return;
    }

    int i, j, tmp;
    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            tmp = arr[j][i];
            arr[j][i] = arr[i][j];
            arr[i][j] = tmp;
        }
    }

    showme_ext(arr, size);

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size / 2; j++)
        {
            tmp = arr[i][j];
            arr[i][j] = arr[i][size - j - 1];
            arr[i][size - j - 1] = tmp;
        }
    }

    showme_ext(arr, size);
}




int main()
{
    //int ret;
    //ret = pow(2, 3);
    //printf("ret = %d\n", ret);

    //ret = rec_2(7);
    //printf("ret = %d\n", ret);

    //char str[] = "12345";
    //printf("%s\n", revers(str));

    int arr[3][3] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};
    rotate(arr, 3);
    return 0;
}