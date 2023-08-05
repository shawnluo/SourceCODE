#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


#define SIZE 100

/*
    arr[] as a target
    tmp[] as a temp
    arr1[] left,        mid
    arr2[] mid + 1,     right
*/
void merge(int arr[], int left, int mid, int right)
{
    int aux[SIZE] = {0};
    int i, j, k;

    for(i = left, j = mid + 1, k = 0; k <= right - left; k++)
    {
        if(i == mid + 1)    //if arr1 reach to the end, then copy arr2 remain elements to aux;
        {
            aux[k] = arr[j++];
            continue;
        }
        if(j == right + 1)    //if arr2 reach to the end, then copy arr1 remain elements to aux;
        {
            aux[k] = arr[i++];
            continue;
        }

        if(arr[i] < arr[j])
        {
            aux[k] = arr[i++];
        }
        else
        {
            aux[k] = arr[j++];
        }
    }

    //copy aux[] back to arr[]
    for(i = left, j = 0; i <= right; i++, j++)
    {
        arr[i] = aux[j];
    }
}


void merge_sort_ext(int arr[], int low, int high)
{
    if(low < high)
    {
        int mid = (low + high) / 2;
        merge_sort_ext(arr, low, mid);
        merge_sort_ext(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void showme(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
#if 0
    int arr[] = {3, 700, 8, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    printArr(arr, n);
#endif

    int arr[] = {3, 700, 8, 1, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    merge_sort_ext(arr, 0, n - 1);
    showme(arr, n);

	return 0;
}