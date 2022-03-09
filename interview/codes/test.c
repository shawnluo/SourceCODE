#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <limits.h>


void merge(int *arr, int left, int mid, int right)
{
    int i, j, k;
    int tmp[100] = {0};
    for(i = left, j = mid + 1, k = 0; k <= (right - left); k++)
    {
        if(i == mid + 1)
        {
            tmp[k] = arr[j++];
            continue;
        }
        if(j == right + 1)
        {
            tmp[k] = arr[i++];
            continue;
        }

        if(arr[i] < arr[j])
        {
            tmp[k] = arr[i++];
        }
        else
        {
            tmp[k] = arr[j++];
        }
    }

#if 0
    for(i = 0; i <= right - left; i++)
    {
        printf("%d ", tmp[i]);
    }
    printf("\n");

    for(i = 0; i <= right - left; i++)
    {
        printf("%d ", tmp[i]);
        arr[left] = tmp[i];
        left++;
    }
#else
    for(i = 0; i <= right - left; i++)
    {
        printf("%d ", tmp[i]);
    }
    printf("\n");

    for(i = left, j = 0; i <= right; i++, j++)
    {
        printf("%d ", tmp[j]);
        arr[i] = tmp[j];
    }
#endif
}

void merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void showme(int *arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {21, 8, 987, -12, 76};
    int size = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, 0, size - 1);
    //showme(arr, size);

	return 0;
}