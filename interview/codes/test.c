
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


/*
    pivot, 
    from left,      int *pL     all elements <= pivot
    from right,     int *pR     all elements > pivot
    quick_sort(arr, left, pivot - 1);
    quick_sort(arr, pivot + 1, right);
*/

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = (left - 1);

    for(int j = left; j <= right - 1; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            printf("%d : %d\n", arr[i], arr[j]);
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[right]);
    return (i + 1);
}


void quick_sort(int *arr, int left, int right)
{
    if(left < right)
    {
        int pivot = partition(arr, left, right);
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}

void printArr(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {10, 7, 8, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    printArr(arr, n);

	return 0;
}