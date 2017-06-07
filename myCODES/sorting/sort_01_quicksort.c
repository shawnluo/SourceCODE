

#include <stdio.h>
#include <stdlib.h>

void showme(int *arr, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        printf("%d, ", arr[i]);
    }

    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

void quicksort(int *arr, int start, int end)
{
    int left, right;

    if (start < end)
    {
        left  = start + 1;
        right = end;

        while (left <= right)
        {
            while (arr[left] <= arr[start])
            {
                left++;
            }

            while (arr[right] > arr[start])
            {
                right--;
            }

            if (left < right)
            {
                swap(&arr[left], &arr[right]);
            }
        }

        swap(&arr[start], &arr[right]);
        quicksort(arr, start, right - 1);
        quicksort(arr, right + 1, end);
    }
}

int main(void)
{
    int  *arr;
    int  len, i;

    printf("Please input arr length: ");

    scanf("%d", &len);

    arr = (int *)malloc(len * sizeof(int));
    if (!arr)
    {
        printf("failed to create arr!\n");
        exit(1);
    }

    for (i = 0; i < len; i++)
    {
        scanf("%d", &arr[i]);
    }

    showme(arr, len);
    quicksort(arr, 0, len - 1);
    showme(arr, len);
    free(arr);

    return 0;
}
