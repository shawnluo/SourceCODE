#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void showme(int *p1, int *p2)
{
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void sort_bubble(int *arr, int len)
{
    assert(arr);

    int i, j;

    for(i = 0; i < len; i++)
    {
        for(j = 0; j < len - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

int main(void)
{
    int arr[5] = {1, 21, 5, 0, 98};
    int len = sizeof(arr) / sizeof(arr[0]);
    sort_bubble(arr, len);

    return 0;
}