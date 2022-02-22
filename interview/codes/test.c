
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>


void showme(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *p1, int *p2)
{
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void sorting_bubble(int *arr, int len)
{
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

/*
    from the first one, insert the element to the right position
*/
void sorting_ins(int *arr, int len)
{
    int i, j, save;
    for(i = 1; i < len; i++)
    {
        save = arr[i];
        j = i - 1;

        // save the current element, compare it with the front elements.
        // if the saved element less than the front elements, then swap with it.
        while(j >= 0 && save < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }
        // until find the element bigger than saved one, then set it to saved one.
        arr[j + 1] = save;
    }
}

int main()
{
    int arr[] = { 117, 15, 72, 88, 98, 332, -1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    sorting_bubble(arr, len);
    showme(arr, len);

    return 0;
}
