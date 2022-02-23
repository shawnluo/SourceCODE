
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


/*
        1.7 write an algorithm such that if an element in an MxN matrix is 0, then set its entire row and column to 0
            1 0 1      -->      0 0 0
            1 1 1               1 0 1
*/


/*
    set arr[][j] and arr[i][] to 0;
*/
void set_newArr(int arr[5][5], int x, int y, int i, int j)
{
    int row, col;

    for(row = 0; row < x; row++)
    {
        arr[row][j] = 1;
    }

    for(col = 0; col < y; col++)
    {
        arr[i][col] = 1;
    }
}

/*
    1. create a new arr, set all the elements to 0
    2. go through the arr, if find element is 0c then mark the row and column to 1 in the new arr.
    3. compare the 2 arrarys, any elements in the new arr marked as 1, then set it to 0 in the arr. 
*/
int mark_matrix(int arr[5][5], int x, int y)
{
    int newArr[10][10] = {0};

    int i, j;

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(arr[i][j] == 0)
            {
                printf("i = %d, j = %d, x = %d, y = %d\n", i, j, x, y);
                set_newArr(newArr, x, y, i, j);
            }
        }
    }

    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(newArr[i][j] == 1)
            {
                arr[i][j] = 0;
            }
        }
    }

    printf("------ arr ------\n");
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            printf("%d, ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main()
{
    int arr[5][5] = {   {1, 0, 1, 1, 1},
                        {1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 1}
    };

    int ret = mark_matrix(arr, 5, 5);

    //printf("%d\n", ret);
    //printf("%s\n", str_new);

    return 0;
}
